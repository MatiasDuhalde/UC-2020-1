#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "../common/file_handling.h"

// EJECUCIÓN
// ./osrs <file> <output> <version> [<quantum>]
// file: path del archivo a leer como input
// output: path de un archivo en formato csv con las estadísticas de simulación
// version: {p, np} especifica si se usa preemptive o non-preemptive
// quantum: opcional, denota el quantum del scheduler, por defecto es 5 

void np_scheduler(char* input_path, char* output_path) {

    Queue* queue = get_procesos(input_path);

    int n_procesos = queue->n_procesos;
    int remaining_processes = n_procesos;

    printf("Iniciando STRF non-preemptive scheduler con %d procesos Cx\n\n", n_procesos);

    int ticks = 0;
    int PID_counter = 0;
    Process* CPU_process = NULL;

    printf("TICK %d\n", ticks);
    while (remaining_processes > 0) {
        // Check for starting time (activate processes)
        if (PID_counter < n_procesos) {
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                // Check if process arrived to the queue
                if (current_process->tiempo_inicio == ticks && !current_process->active) {
                    printf("PROCESS: %s JUST ARRIVED!\n", current_process->nombre);
                    current_process->status = READY;
                    current_process->active = 1;
                    current_process->PID = PID_counter;
                    PID_counter++;
                }
            }
        }

        // CHECK FOR READY PROCESSES
        // Also check for ready process that has shortest remaining time
        if (PID_counter > 0) {
            int priority_process_initialized = 0;
            int any_ready_process = 0;
            Process* current_priority_process;
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                current_process->fresh_out = 0;
                // NESTED IFS HELL, sorry
                if (current_process->active && current_process->status == READY) {
                    printf("PROCESS: %s IS READY!\n", current_process->nombre);
                    any_ready_process = 1;
                    if (!priority_process_initialized) {
                        // First ready process found enters here and gets temporarily chosen
                        current_priority_process = current_process;
                        priority_process_initialized = 1;
                    }
                    if (current_process->CPU_time_remaining <
                        current_priority_process->CPU_time_remaining) {
                        // If time remaining is lesser
                        current_priority_process = current_process;
                    } else if (current_process->CPU_time_remaining ==
                        current_priority_process->CPU_time_remaining) {
                        // If there's a tie
                        if (current_process->bursts[current_process->current_burst_index] <
                            current_priority_process->bursts[current_priority_process->current_burst_index]) {
                            // If next burst is lesser
                            current_priority_process = current_process;
                        } else if (current_process->bursts[current_process->current_burst_index] ==
                            current_priority_process->bursts[current_priority_process->current_burst_index]) {
                            // If there's a tie yet again
                            if (current_process->PID < current_priority_process->PID) {
                                // If PID is lesser
                                current_process = current_priority_process;
                            }
                        }
                    }
                }
            }
            // If CPU is idle and at least one READY process was found
            // put priority process in the CPU
            if (CPU_process == NULL && any_ready_process && priority_process_initialized) {
                CPU_process = current_priority_process;
                CPU_process->status = RUNNING;
                CPU_process->turnos++;
            }
        }

        // DECREMENT WAITING PROCESSES
        if (PID_counter > 0) {
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                if (current_process->active && current_process->status == WAITING) {
                    printf("PROCESS: %s IS WAITING!\n", current_process->nombre);
                    current_process->bursts[current_process->current_burst_index]--;
                    if (current_process->bursts[current_process->current_burst_index] == 0) {
                        printf("PROCESS: %s IS DONE WAITING!\n", current_process->nombre);
                        current_process->current_burst_index++;
                        current_process->status = READY;
                    }
                }
            }
        }

        // DECREMENT RUNNING PROCESS
        if (CPU_process) {
            printf("PROCESS: %s IS RUNNING!\n", CPU_process->nombre);
            CPU_process->bursts[CPU_process->current_burst_index]--;
            CPU_process->CPU_time_remaining--;
            if (CPU_process->bursts[CPU_process->current_burst_index] == 0) {
                printf("PROCESS: %s IS DONE RUNNING!\n", CPU_process->nombre);
                CPU_process->current_burst_index++;
                // Finish process if no CPU bursts remaining
                if (CPU_process->CPU_time_remaining == 0) {
                    CPU_process->status = FINISHED;
                    remaining_processes--;
                } else {
                    CPU_process->status = WAITING;
                }
                CPU_process->fresh_out = 1;
                CPU_process = NULL;
            }
        }

        // CHECK STATS
        if (PID_counter > 0) {
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                // Check turnaround time
                if ((current_process->active && current_process->status != FINISHED) ||
                    (current_process->fresh_out && current_process->status == FINISHED)) {
                    current_process->turnaround_time++;
                }
                // Check response time
                if (current_process->active && current_process->status == READY &&
                    current_process->turnos == 0) {
                    current_process->response_time++;
                }
                // Check waiting time
                if (current_process->active && !current_process->fresh_out &&
                    (current_process->status == READY || current_process->status == WAITING)) {
                    current_process->waiting_time++;
                }
            }
        }

        // Increment tick
        ticks++;
        printf("TICK %d\n", ticks);
    }

    output_csv(output_path, queue);
    free_queue(queue);
}

void p_scheduler(char* input_path, char* output_path, int quantum) {

    Queue* queue = get_procesos(input_path);

    int n_procesos = queue->n_procesos;
    int remaining_processes = n_procesos;

    printf("Iniciando STRF non-preemptive scheduler con %d procesos Cx\n\n", n_procesos);

    int ticks = 0;
    int quantum_counter = 0;
    int PID_counter = 0;
    Process* CPU_process = NULL;

    printf("TICK %d\n", ticks);
    while (remaining_processes > 0) {
        // Check for starting time (activate processes)
        if (PID_counter < n_procesos) {
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                // Check if process arrived to the queue
                if (current_process->tiempo_inicio == ticks && !current_process->active) {
                    printf("PROCESS: %s JUST ARRIVED!\n", current_process->nombre);
                    current_process->status = READY;
                    current_process->active = 1;
                    current_process->PID = PID_counter;
                    PID_counter++;
                }
            }
        }

        // CHECK FOR READY PROCESSES
        // Also check for ready process that has shortest remaining time
        if (PID_counter > 0) {
            int priority_process_initialized = 0;
            int any_ready_process = 0;
            Process* current_priority_process;
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                current_process->fresh_out = 0;
                // NESTED IFS HELL, sorry
                if (current_process->active && current_process->status == READY) {
                    printf("PROCESS: %s IS READY!\n", current_process->nombre);
                    any_ready_process = 1;
                    if (!priority_process_initialized) {
                        // First ready process found enters here and gets temporarily chosen
                        current_priority_process = current_process;
                        priority_process_initialized = 1;
                    }
                    if (current_process->CPU_time_remaining <
                        current_priority_process->CPU_time_remaining) {
                        // If time remaining is lesser
                        current_priority_process = current_process;
                    } else if (current_process->CPU_time_remaining ==
                        current_priority_process->CPU_time_remaining) {
                        // If there's a tie
                        if (current_process->bursts[current_process->current_burst_index] <
                            current_priority_process->bursts[current_priority_process->current_burst_index]) {
                            // If next burst is lesser
                            current_priority_process = current_process;
                        } else if (current_process->bursts[current_process->current_burst_index] ==
                            current_priority_process->bursts[current_priority_process->current_burst_index]) {
                            // If there's a tie yet again
                            if (current_process->PID < current_priority_process->PID) {
                                // If PID is lesser
                                current_process = current_priority_process;
                            }
                        }
                    }
                }
            }
            // If CPU is idle and at least one READY process was found
            // put priority process in the CPU
            if (CPU_process == NULL && any_ready_process && priority_process_initialized) {
                CPU_process = current_priority_process;
                CPU_process->status = RUNNING;
                CPU_process->turnos++;
                quantum_counter = 0;
            }
        }

        // DECREMENT WAITING PROCESSES
        if (PID_counter > 0) {
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                if (current_process->active && current_process->status == WAITING) {
                    printf("PROCESS: %s IS WAITING!\n", current_process->nombre);
                    current_process->bursts[current_process->current_burst_index]--;
                    if (current_process->bursts[current_process->current_burst_index] == 0) {
                        printf("PROCESS: %s IS DONE WAITING!\n", current_process->nombre);
                        current_process->current_burst_index++;
                        current_process->status = READY;
                    }
                }
            }
        }

        // DECREMENT RUNNING PROCESS
        if (CPU_process) {
            printf("PROCESS: %s IS RUNNING!\n", CPU_process->nombre);
            CPU_process->bursts[CPU_process->current_burst_index]--;
            CPU_process->CPU_time_remaining--;
            quantum_counter++;
            if (CPU_process->bursts[CPU_process->current_burst_index] == 0 ||
                quantum_counter == quantum) {
                if (CPU_process->bursts[CPU_process->current_burst_index] == 0) {
                    printf("PROCESS: %s IS DONE RUNNING!\n", CPU_process->nombre);
                    CPU_process->current_burst_index++;
                    // If quantum finishes at the same time as burst it also
                    // counts as an interruption, somehow :(
                    if (quantum_counter == quantum) {
                        CPU_process->interrupciones++;
                    }
                    // Finish process if no CPU bursts remaining, else go wait
                    if (CPU_process->CPU_time_remaining == 0) {
                        CPU_process->status = FINISHED;
                        remaining_processes--;
                    } else {
                        CPU_process->status = WAITING;
                    }
                } else {
                    printf("PROCESS: %s WAS KICKED OUT OF THE CPU!\n", CPU_process->nombre);
                    // In this case process is still ready to run
                    CPU_process->status = READY;
                    CPU_process->interrupciones++;
                }
                CPU_process->fresh_out = 1;
                CPU_process = NULL;
            }

        }

        // CHECK STATS
        if (PID_counter > 0) {
            for (int i = 0; i < n_procesos; i++) {
                Process* current_process = queue->procesos[i];
                // Check turnaround time
                if ((current_process->active && current_process->status != FINISHED) ||
                    (current_process->fresh_out && current_process->status == FINISHED)) {
                    current_process->turnaround_time++;
                }
                // Check response time
                if (current_process->active && current_process->status == READY &&
                    current_process->turnos == 0) {
                    current_process->response_time++;
                }
                // Check waiting time
                if (current_process->active && !current_process->fresh_out &&
                    (current_process->status == READY || current_process->status == WAITING)) {
                    current_process->waiting_time++;
                }
            }
        }

        // Increment tick
        ticks++;
        printf("TICK %d\n", ticks);
    }

    output_csv(output_path, queue);
    free_queue(queue);
}


void main(int argc, char* argv[]) {
    // ARGV = (input, output, version, [quantum])
    // ARGC = {4, 5}

    if (argc != 4 && argc != 5) {
        printf("Argumentos incorrectos.\n");
        printf("Terminando programa...\n");
        exit(1);
    }

    char* input_path = argv[1];
    char* output_path = argv[2];
    char* version = argv[3];
    int quantum = (argc == 4) ? 5 : parse_int(argv[4]);

    if (strcmp(version, "np") && strcmp(version, "p")) {
        printf("La versión %s no existe, intente con 'p' o 'np'.\n", version);
        exit(1);
    }
    if (quantum <= 0) {
        printf("quantum %d??? wen chiste m3n\n", quantum);
        exit(1);
    }

    if (strcmp(version, "np") == 0) {
        np_scheduler(input_path, output_path);
    } else if (strcmp(version, "p") == 0) {
        p_scheduler(input_path, output_path, quantum);
    }
}
