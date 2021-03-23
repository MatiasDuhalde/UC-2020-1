#include <stdio.h>

int main(int argc, char* argv[]) {
    
    printf("Ingresaste %d argumentos\n", argc); // argc es la cantidad de argumentos

    for (int i = 0; i < argc; i++) { // Iteramos sobre argc

        printf("Argumento número %d: %s\n", i + 1, argv[i]); // El arreglo argv contiene los argumentos en orden

    };

}