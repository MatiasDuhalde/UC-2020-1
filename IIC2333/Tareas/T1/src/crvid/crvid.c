#include <stdio.h>      // printf
#include <stdlib.h>     // 
#include <signal.h>     // signals
#include <sys/wait.h>
#include <unistd.h>     // fork
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "../common/game_of_life.h"

// GLOBALS
int** instrucciones_ptr;
int** tableros_ptr;
pid_t parent_pid;
int child_pids[20];
int subprocesos[20];
pid_t base_pid;
/* 
-------------------------------------------------------------------------------
LIBERA MEMORIA EN PUNTEROS instrucciones_ptr y tableros_ptr
-------------------------------------------------------------------------------
*/
void free_allocated_memory() {
    printf("FREEING MEMORY \n");
    // FREE INSTRUCCIONES
    int instrucciones_length = (int) (long) instrucciones_ptr[0];
    for (int i = 1; i < instrucciones_length; i++) {
        free(instrucciones_ptr[i]);
    }
    free(instrucciones_ptr);

    // FREE TABLEROS
    int tableros_length = (int) (long) tableros_ptr[0];
    for (int i = 1; i < tableros_length; i++) {
        free(tableros_ptr[i]);
    }
    free(tableros_ptr);
}

/*
-------------------------------------------------------------------------------
SIGNAL HANDLERS
-------------------------------------------------------------------------------
*/

void sigalrm_handler(int signum) {
    printf("[%d]-> GEN: SE ACABÓ EL TIEMPO\n", getpid());
    int n = child_pids[0];
    for (int i = 1; i <= n; i++) {
        printf("KILLING PID: %d\n", child_pids[i]);
        kill(child_pids[i], SIGTERM);
    }
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);
    join_csv(subprocesos);
    free_allocated_memory();
    exit(0);
}

void sigint_handler(int signum) {
    printf("[%d]-> GEN: ALGUIEN APRETÓ CTRL + C?\n", getpid());
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);
    if (getpid() != base_pid) {
        join_csv(subprocesos);
    }
    free_allocated_memory();
    exit(0);
}

/*}
-------------------------------------------------------------------------------
ARGV VALIDATION
-------------------------------------------------------------------------------
*/
int is_valid_args(int argc, char* argv[]) {
    int status = 1;
    if (argc != 3 || !is_valid_int(argv[2])) {
        status = 0;
    }
    return status;
}

/*
-------------------------------------------------------------------------------
LAUNCH GAME
-------------------------------------------------------------------------------
*/
void launch_game(int line_index) {
    int tipo = instrucciones_ptr[line_index + 1][0];
    int iteraciones = instrucciones_ptr[line_index + 1][1];
    int A = instrucciones_ptr[line_index + 1][2];
    int B = instrucciones_ptr[line_index + 1][3];
    int C = instrucciones_ptr[line_index + 1][4];
    int D = instrucciones_ptr[line_index + 1][5];
    int tablero_index = instrucciones_ptr[line_index + 1][6] + 1;
    int n_cells = tableros_ptr[tablero_index][0];
    int* tablero = malloc(sizeof(int) * (2 * n_cells + 1));
    for (int i = 0; i < 2 * n_cells + 1; i++) {
        tablero[i] = tableros_ptr[tablero_index][i];
    }
    free_allocated_memory();
    start_game_of_life(iteraciones, A, B, C, D, line_index, tablero);
}

/*
-------------------------------------------------------------------------------
FLUJO DE PROCESOS
-------------------------------------------------------------------------------
*/

void generate(int line_index) {
    int tipo = instrucciones_ptr[line_index + 1][0];
    int tiempo = instrucciones_ptr[line_index + 1][1];
    int n = instrucciones_ptr[line_index + 1][2];
    parent_pid = getpid();
    child_pids[0] = n;
    subprocesos[0] = n;
    subprocesos[1] = line_index;


    // START ALARM??
    alarm(tiempo);
    printf("SOY EL PROCESO GENERADOR %d\n", getpid());
    printf("CREANDO %d SUBPROCESOS...\n", n);
    pid_t child_pid;
    for (int i = 0; i < n; i++) {
        subprocesos[i + 2] = instrucciones_ptr[line_index + 1][3 + i];
        child_pid = fork();
        if (child_pid == -1) {
            printf("ERROR AL CREAR PROCESO\n");
            exit(1);
        }
        if (child_pid == 0) {
            int new_line_index = instrucciones_ptr[line_index + 1][3 + i];
            int new_type = instrucciones_ptr[new_line_index + 1][0];
            if (new_type == 0) {
                // OTRO PROCESO GENERADOR
                printf("[%d] HA CREADO EL PROCESO GENERADOR %d\n", getppid(), getpid());
                generate(new_line_index);
                free_allocated_memory();
                exit(0);
            }
            else if (new_type == 1) {
                // PROCESO SIMULADOR
                signal(SIGINT, sigint_sim_handler);
                printf("[%d] HA CREADO EL PROCESO SIMULADOR %d\n", getppid(), getpid());
                launch_game(new_line_index);
                exit(0);
            }
        }
        else {
            child_pids[i + 1] = child_pid;
        }
    }
    printf("TERMINÉ DE CREAR %d SUBPROCESOS...\n", n);
    printf("AHORA VOY A ESPERAR...\n");
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);
    printf("[%d] TERMINÉ DE ESPERAR!\n", getpid());
    join_csv(subprocesos);
    free_allocated_memory();
    exit(0);
}

/*
-------------------------------------------------------------------------------
MAIN
-------------------------------------------------------------------------------
*/
void main(int argc, char* argv[]) {

    // GET AND VALIDATE ARGUMENTS
    if (!is_valid_args(argc, argv)) {
        printf("Argumentos incorrectos.\n");
        printf("Terminando programa...\n");
        exit(1);
    }
    const char* input_file_path = argv[1];
    int line_index = atoi(argv[2]);
    const char* tablero_file_path = "tableros.txt";

    // DEBUG OUTPUT
    printf("ARGUMENTOS:\n - INPUT_PATH: %s\n - LINE_INDEX: %d\n\n", input_file_path, line_index);

    // EXTRACT FROM FILES
    instrucciones_ptr = get_instrucciones_array(input_file_path);
    tableros_ptr = get_tablero_array(tablero_file_path);

    // VALIDATE line_index
    if (line_index < 0 || line_index >= (int) (long) instrucciones_ptr[0] - 1) {
        printf("WRONG ARGUMENT: line_index can't be %d\n", line_index);
        free_allocated_memory();
        exit(1);
    }

    // Linkear signals????
    signal(SIGINT, sigint_handler);
    signal(SIGALRM, sigalrm_handler);

    base_pid = getpid();

    printf("EMPEZANDO PROCESOS...\n");
    int process_type = instrucciones_ptr[line_index + 1][0];
    if (process_type == 0) {
        // Si parte con un proceso generador, se crea el primer proceso acá y luego genera
        // los sub-procesos
        pid_t child_pid = fork();
        if (child_pid == -1) {
            printf("ERROR AL CREAR PROCESO\n");
            exit(1);
        }
        if (child_pid == 0) {
            printf("[%d] CREÓ EL PRIMER PROCESO GENERADOR %d\n", getppid(), getpid());
            generate(line_index);
        }
    }
    else if (process_type == 1) {
        // Si parte con un proceso simulador basta con ejecutar el juego.
        printf("[%d] CREÓ EL PRIMER PROCESO SIMULADOR %d\n", getppid(), getpid());
        launch_game(line_index);
    }
    // Esperar a que termine el primer proceso :o
    printf("AHORA VOY A ESPERAR...\n");
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);
    printf("[%d] TERMINÉ DE ESPERAR!\n", getpid());

    free_allocated_memory();
}
