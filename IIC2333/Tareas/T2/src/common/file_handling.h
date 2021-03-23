#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "int_handling.h"
#include "objects.h"
#define BUFFER_SIZE 65566

void output_csv(const char* output_path, Queue* queue) {
    FILE* fptr;
    // Output line format:
    // nombre_proceso_i,turnos_CPU_i,interrupciones_i,turnaround_time_i,response_time_i,waiting_time_i
    fptr = fopen(output_path, "w");
    for (int i = 0; i < queue->n_procesos; i++) {
        fprintf(fptr, "%s,%d,%d,%d,%d,%d\n",
                queue->procesos[i]->nombre,
                queue->procesos[i]->turnos,
                queue->procesos[i]->interrupciones,
                queue->procesos[i]->turnaround_time,
                queue->procesos[i]->response_time,
                queue->procesos[i]->waiting_time);
    }
    fclose(fptr);
}

// First line of input file contains number N of lines to read
// Next N lines contain the processes and their attributes. Format:
// NOMBRE_PROCESO TIEMPO_INICIO N A_1 B_1 A_2 B_2 ... A_N-1 B_N-1 A_N
Queue* get_procesos(const char* input_path) {
    FILE* fptr;
    char str[BUFFER_SIZE];

    // Open file and check for existence
    if ((fptr = fopen(input_path, "r")) == NULL) {
        printf("ERROR: el archivo %s no existe.\n", input_path);
        exit(1);
    }
    fgets(str, BUFFER_SIZE, fptr); // Get first line containing n of processes
    int n_procesos = parse_int(strtok(str, "\n "));

    Queue* queue = create_queue(n_procesos);
    for (int i = 0; i < n_procesos; i++) {
        fgets(str, BUFFER_SIZE, fptr); // Get subsequent lines
        char* nombre = strtok(str, "\n ");
        int tiempo_inicio = parse_int(strtok(NULL, "\n "));
        int n_bursts = parse_int(strtok(NULL, "\n "));
        int* bursts = malloc(sizeof(int) * (n_bursts * 2 - 1));
        int CPU_time_remaining = 0;
        for (int j = 0; j < n_bursts * 2 - 1; j++) {
            bursts[j] = parse_int(strtok(NULL, "\n "));
            if (j % 2 == 0) {
                CPU_time_remaining += bursts[j];
            }
        }
        Process* proceso = create_process(nombre, tiempo_inicio, n_bursts, bursts, CPU_time_remaining);
        queue->procesos[i] = proceso;
    }
    fclose(fptr);
    return queue;
}
