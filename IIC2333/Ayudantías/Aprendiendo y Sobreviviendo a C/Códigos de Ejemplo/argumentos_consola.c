#include <stdio.h>

// Para compilar este código puedes utilizar el comando gcc -o exe argumentos_consola.c

int main(int argc, char const *argv[])
{
    // Usualmente los scripts pueden recibir argumentos, de la forma ./script argumento_1, .., argumento_N
    // Para implementar esto tenemos los argumentos argc (cantidad de argumentos)
    // y argv (los argumentos en si)

    // Corre este código con distintos argumentos y ve lo que pasa con estas variables.
    printf("La cantidad de argumentos es: %d\n", argc);
    printf("Los argumentos son:\n");
    for (int i = 0; i < argc; i++)
    {
        printf("\t%d.- %s\n", i + 1, argv[i]);
    }

    // Por ejemplo, intenta correr este programa de la forma "./exe hola como estas"
    return 0;
}
