#include <stdio.h>      // printf
#include <stdlib.h>     // 
#include <string.h>
#include "int_handling.h"
#define BUFFER_SIZE 1024

void output_csv(int line_number, int cant_celulas, int iters, const char* razon_termino) {
    FILE* fptr;
    int length = snprintf(NULL, 0, "%d.csv", line_number);
    char* file_path = malloc(length + 1);
    snprintf(file_path, length + 1, "%d.csv", line_number);
    fptr = fopen(file_path, "w");
    free(file_path);
    fprintf(fptr, "%d, %d, %s", cant_celulas, iters, razon_termino);
    fclose(fptr);
}

void join_csv(int* lista_sp) {
    int n_sp = lista_sp[0];
    int line_number = lista_sp[1];
    printf("LINE_NUMBER: %d\n", line_number);
    printf("IM: %d\n", getpid());
    FILE* fptr;
    int length = snprintf(NULL, 0, "%d.csv", line_number);
    char* file_path = malloc(length + 1);
    snprintf(file_path, length + 1, "%d.csv", line_number);
    fptr = fopen(file_path, "w");
    free(file_path);
    for (int i = 2; i < n_sp + 2; i++){
        FILE* sp_fptr;
        int sp_length = snprintf(NULL, 0, "%d.csv", lista_sp[i]);
        char* sp_file_path = malloc(sp_length + 1);
        snprintf(sp_file_path, sp_length + 1, "%d.csv", lista_sp[i]);
        sp_fptr = fopen(sp_file_path, "r");
        free(sp_file_path);

        fseek(sp_fptr, 0, SEEK_END);
        long fsize = ftell(sp_fptr);
        fseek(sp_fptr, 0, SEEK_SET);
        char contents[fsize + 1];
        fread(contents, 1, fsize, sp_fptr);
        contents[fsize] = '\0';

        fprintf(fptr, "%s\n", contents);
        fclose(sp_fptr);
    }
    fclose(fptr);
}

// Get the number of valid lines of a file
// A valid line starts with a number
// Empty lines ignored
int count_valid_lines(const char* path) {
    FILE* fptr;
    char str[BUFFER_SIZE];
    char* pch;
    if ((fptr = fopen(path, "r")) == NULL) {
        printf("ERROR: el archivo %s no existe.\n", path);
        exit(1);
    }
    int line_counter = 0;
    while (fgets(str, BUFFER_SIZE, fptr) != NULL) {
        pch = strtok(str, "\n ");
        if (is_valid_int(pch)) {
            line_counter += 1;
        }
    }
    fclose(fptr); // CLOSE FILE
    return line_counter;
}

// USE JAGGED ARRAYS

int** get_instrucciones_array(const char* path) {
    FILE* fptr;
    int n = count_valid_lines(path);
    int** arrayptr = malloc((n + 1) * sizeof(int*));
    arrayptr[0] = (int*) (long) (n + 1); // LENGTH OF ARRAY
    int counter = 1;

    char str[BUFFER_SIZE];
    if ((fptr = fopen(path, "r")) == NULL) {
        printf("ERROR: el archivo %s no existe.\n", path);
        exit(1);
    }

    while (fgets(str, BUFFER_SIZE, fptr) != NULL) {
        int process_type = parse_int(strtok(str, "\n "));
        if (process_type == 0) { // TYPE GENERATOR PROCESS
            int process_time = parse_int(strtok(NULL, "\n "));
            int process_n = parse_int(strtok(NULL, "\n "));
            int* process_params = malloc((3 + process_n) * sizeof(int));
            process_params[0] = process_type;
            process_params[1] = process_time;
            process_params[2] = process_n;
            for (int i = 0; i < process_n; i++) {
                process_params[i + 3] = parse_int(strtok(NULL, "\n "));
            }
            arrayptr[counter] = process_params;
            counter++;
        }
        else if (process_type == 1) { // TYPE SIMULATOR PROCESS
            int* process_params = malloc(7 * sizeof(int));
            process_params[0] = process_type;
            for (int i = 1; i < 7; i++) {
                process_params[i] = parse_int(strtok(NULL, "\n "));
            }
            arrayptr[counter] = process_params;
            counter++;
        }
        else {
            printf("ERROR: Invalid process type.\n");
            exit(1);
        }

    }
    fclose(fptr); // CLOSE FILE
    return arrayptr;
}


int** get_tablero_array(const char* path) {
    FILE* fptr;
    int n = count_valid_lines(path);
    int** arrayptr = malloc((n + 1) * sizeof(int*));
    arrayptr[0] = (int*) (long) (n + 1); // LENGTH OF ARRAY
    int counter = 1;

    char str[BUFFER_SIZE];
    if ((fptr = fopen(path, "r")) == NULL) {
        printf("ERROR: el archivo %s no existe.\n", path);
        exit(1);
    }

    while (fgets(str, BUFFER_SIZE, fptr) != NULL) {
        int cell_number = parse_int(strtok(str, "\n "));
        int* tablero_params = malloc((1 + 2*cell_number) * sizeof(int));
        tablero_params[0] = cell_number;
        for (int i = 1; i < (1 + 2*cell_number); i++) {
            tablero_params[i] = parse_int(strtok(NULL, "\n "));
        }
        arrayptr[counter] = tablero_params;
        counter++;
    }
    fclose(fptr); // CLOSE FILE
    return arrayptr;
}
