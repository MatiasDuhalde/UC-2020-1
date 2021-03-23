#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep
#include <signal.h>
#include "../common/file_handling.h"
 
#define for_x for (int x = 0; x < D; x++)
#define for_y for (int y = 0; y < D; y++)
#define for_xy for_x for_y

// Adaptado desde https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C
// La base es la misma, pero se suprime el print, se añade el manejo de csv,
// y se agregan los parámetros del enunciado


int n_linea;
int cantidad_celulas_vivas;
int counter;
int dimension;
int free_aux;
unsigned** univ;
unsigned** new_tablero;


void sigterm_sim_handler(int signum) {
    printf("[%d]-> SIM: ME LLEGÓ SIGTERM\n", getpid());
    output_csv(n_linea, cantidad_celulas_vivas, counter, "SIGNAL");
    for (int i = 0; i < dimension; i++) {
        free(univ[i]);
    }
    free(univ);
    if (free_aux == 1) {
        for (int i = 0; i < dimension; i++) {
            free(new_tablero[i]);
        }
        free(new_tablero);
    }

    exit(0);
}

void sigint_sim_handler(int signum) {
    printf("[%d]-> SIM: ALGUIEN APRETÓ CTRL + C?\n", getpid());
    output_csv(n_linea, cantidad_celulas_vivas, counter, "SIGNAL");
    for (int i = 0; i < dimension; i++) {
        free(univ[i]);
    }
    free(univ);
    if (free_aux == 1) {
        for (int i = 0; i < dimension; i++) {
            free(new_tablero[i]);
        }
        free(new_tablero);
    }
    exit(0);
}

void show(unsigned **u, int D) {
    unsigned **univ = u;
    printf("\033[H");
    for_y {
        for_x printf(univ[y][x] ? "\033[07m  \033[m" : "  ");
        printf("\033[E");
    }
    fflush(stdout);
}

void evolve(unsigned **u, int A, int B, int C, int D)
{
    unsigned **univ = u;
    new_tablero = malloc(D * sizeof(unsigned*));
    for (int i = 0; i < D; i++) {
        new_tablero[i] = malloc(D * sizeof(unsigned));
    }
    free_aux = 1;


    for_y for_x {
        int n = 0;
        for (int y1 = y - 1; y1 <= y + 1; y1++)
            for (int x1 = x - 1; x1 <= x + 1; x1++)
                if (univ[(y1 + D) % D][(x1 + D) % D])
                    n++;
 
        if (univ[y][x]) n--;

        new_tablero[y][x] = (n == A || ((n >= B && n <= C) && univ[y][x]));
    }
    for_y for_x univ[y][x] = new_tablero[y][x];

    free_aux = 0;
    for (int i = 0; i < D; i++) {
        free(new_tablero[i]);
    }
    free(new_tablero);
}

int count_cells(unsigned **u, int D) {
    unsigned **univ = u;
    int count = 0;
    for_xy if (univ[x][y] == 1) count++;
    return count;
}

void game(int max_iters, int A, int B, int C, int D, int n_linea, int n_celulas, int* pos_celulas) {
    univ = malloc(D * sizeof(unsigned*));
    for (int i = 0; i < D; i++) {
        univ[i] = malloc(D * sizeof(unsigned));
    }

    for_xy univ[x][y] = 0;
    for (int i = 0; i < n_celulas*2; i += 2) {
        int x = pos_celulas[i]; // DESDE 1 a D
        int y = pos_celulas[i + 1]; // DESDE 1 a D
        univ[x - 1][y - 1] = 1;
    }
    cantidad_celulas_vivas = count_cells(univ, D);

    counter = 0;
    while (counter < max_iters) {
        // printf("THERE ARE %d CELLS ALIVE.\n", count_cells(univ, D));
        evolve(univ, A, B, C, D);
        counter++;
        // sleep(1);
        if (count_cells(univ, D) == 0) {
            break;
        }
    }
    cantidad_celulas_vivas = count_cells(univ, D);
    if (counter == max_iters) {
        // SE ACABAN LAS ITERACIONES
        output_csv(n_linea, cantidad_celulas_vivas, counter, "NOTIME");
    }
    else if (cantidad_celulas_vivas == 0) {
        // SE ACABAN LAS CELULAS
        output_csv(n_linea, cantidad_celulas_vivas, counter, "NOCELLS");
    }
    else {
        output_csv(n_linea, cantidad_celulas_vivas, counter, "SIGNAL");
    }
    for (int i = 0; i < D; i++) {
        free(univ[i]);
    }
    free(univ);
}

int start_game_of_life(int max_iters, int A, int B, int C, int D, int n, int* tablero_array) {
    // ARGS: ITERACIONES, A, B, C, D, n_linea, n_celulas, x_1, y_1, ..., x_n, y_n
    signal(SIGTERM, sigterm_sim_handler);
    signal(SIGINT, sigint_sim_handler);
    int n_celulas = tablero_array[0];
    int pos_celulas[2*n_celulas];
    dimension = D;
    for (int i = 0; i < 2*n_celulas; i++) {
        pos_celulas[i] = tablero_array[i + 1];
    }
    n_linea = n;
    free(tablero_array);

    game(max_iters, A, B, C, D, n_linea, n_celulas, pos_celulas);
}
