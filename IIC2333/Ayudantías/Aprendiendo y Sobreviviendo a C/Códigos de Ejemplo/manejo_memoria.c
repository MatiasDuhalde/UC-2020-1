#include <stdio.h>
#include <stdlib.h>

// Para compilar este código puedes utilizar el comando gcc -o exe manejo_memoria.c

int main(int argc, char const *argv[])
{
    // Como hablamos el manejo de memoria es escencial en C, pero exactamente en
    // que caso debemos pedir memoria?
    // Una buena guía es que debes pedir memoria siempre que no sepas de antemano
    // cuantas de esas entidades vas a generar.
    // Por ejemplo, no es necesario pedir memoria para un contador (sabemos que solo será 1)
    // pero si para una lista de input del usuario, o un struct que puede llegar
    // a tener muchas instancias.

    // 1. Pedir memoria para un int
    int *puntero_malloc = malloc(sizeof(int));
    *puntero_malloc = 5;

    int *puntero_calloc = calloc(1, sizeof(int));
    *puntero_calloc = 7;

    printf("Direccion donde esta el puntero: %li (este es el puntero del puntero)\n", &puntero_malloc);
    printf("Direccion a done apunta el puntero: %li\n", puntero_malloc);
    printf("Contenido del puntero: %d\n\n", *puntero_malloc);

    // 2. Pedir memoria para un array de ints
    int cantidad = 3;
    int *nums_malloc = malloc(cantidad * sizeof(int));
    int *nums_calloc = calloc(cantidad, sizeof(int));

    nums_malloc[0] = 2;
    nums_malloc[1] = 1;
    nums_malloc[2] = 5;

    printf("El contenido del array es:[");
    for (size_t i = 0; i < cantidad; i++)
    {
        printf("%d, ", nums_malloc[i]);
    }
    printf("]\n\n");

    // 3. Pedir memoria para un array de arrays de ints.

    // Para hacer una lista de listas (en verdad array de arrays) necesitamos
    // un puntero, que apunte a una seccion de memoria que contenga punteros.
    // Se puede pensar como lo mismo que un array de ints, solo que estos ints
    // resultan ser direcciones de memoria que llevan a un array.

    // Primero debemos pedir memoria para el puntero de punteros, que lleva ** por lo mismo:
    int rows = 2;
    int cols = 3;

    // Nótese la diferencia, no estamos pidiendo memoria para un int, estamos
    // pidiendo memorias a para un puntero que apunta int, por lo cual hacemos
    // sizeof int *.
    int **matriz = malloc(rows * sizeof(int *));

    // Luego debemos pedir memoria para cada uno de los punteros internos
    for (int i = 0; i < rows; i++)
    {
        matriz[i] = malloc(cols * sizeof(int));
    }

    // Ahora podemos rellenar la matriz:
    matriz[0][0] = 1;
    matriz[0][1] = 0;
    matriz[0][2] = 1;
    matriz[1][0] = 0;
    matriz[1][1] = 5;
    matriz[1][2] = 3;

    // Luego la podemos imprimir:
    printf("El contenido de la matriz es:\n[\n");
    for (int i = 0; i < rows; i++)
    {
        printf("\t[");
        for (int j = 0; j < cols; j++)
        {
            printf("%d, ", matriz[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");

    // Finalmente, el proceso para pedir array de arrays de cualquier cosa es el siguiente:
    // 1. cosa **nombre = malloc(cantidad * sizeof(cosa *));
    // 2. nombre[indice] = malloc(cantidad * sizeof(cosa));

    // Como ejercicio corran este programa con valgrind de la sig forma:
    //      valgind ./exe
    // Debido a los mallocs habrán varios memory leaks, su ejercicio es solucionarlos.

    return 0;
}
