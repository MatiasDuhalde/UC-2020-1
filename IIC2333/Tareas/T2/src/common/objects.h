#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum status {RUNNING, READY, WAITING, FINISHED} Status;

// Cuando el proceso termina, cuenta como interrupción al proceso? 
// Estará bien llevar cuenta de las estadísticas aquí? supongo que sí :)
typedef struct Process {
    // Atributos pedidos en el enunciado
    pid_t PID;
    char nombre[32];
    int prioridad; // ??
    Status status;
    // Atributos del archivo
    int tiempo_inicio;
    int n_bursts;
    int* bursts;
    // Estadísticas
    int turnos;
    int interrupciones;
    int turnaround_time;
    int response_time;
    int waiting_time;
    // Atributos auxiliares
    int CPU_time_remaining;
    int current_burst_index;
    int active;
    int fresh_out;

} Process;

// Contiene procesos que puedan estar en READY
typedef struct Queue {
    int n_procesos;
    Process** procesos;
} Queue;

Process* create_process(char* nombre, int tiempo_inicio, int n_bursts,
                        int* bursts, int CPU_time_remaining) {
    Process* process = (Process*) malloc(sizeof(Process));
    strcpy(process->nombre, nombre);
    // process->status = WAITING;
    process->tiempo_inicio = tiempo_inicio;
    process->n_bursts = n_bursts;
    process->bursts = bursts;
    process->CPU_time_remaining = CPU_time_remaining;
    process->current_burst_index = 0;
    process->active = 0;
    // Initialize statistics
    process->turnos = 0;
    process->interrupciones = 0;
    process->turnaround_time = 0;
    process->response_time = 0;
    process->waiting_time = 0;
    process->fresh_out = 0;
    return process;
}

void free_process(Process* process) {
    free(process->bursts);
    free(process);
}

Queue* create_queue(int n_procesos) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->n_procesos = n_procesos;
    queue->procesos = (Process**) calloc(n_procesos, sizeof(Process*));
    // Init ready array??
    return queue;
}

void free_queue(Queue* queue) {
    for (int i = 0; i < queue->n_procesos; i++) {
        free_process(queue->procesos[i]);
    }
    free(queue->procesos);
    free(queue);
}
