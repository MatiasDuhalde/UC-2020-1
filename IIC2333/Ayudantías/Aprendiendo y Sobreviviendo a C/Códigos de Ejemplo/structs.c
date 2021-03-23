#include <stdio.h>
#include <stdlib.h>

// Para compilar este código puedes utilizar el comando gcc -o exe structs.c

// Definamos un dos enum y dos structs:
typedef enum abilidad
{
    INEXISTENTE,
    BAJA,
    PROMEDIO,
    ALTA,
    INFINITA
} Abilidad;

typedef enum estilo_computador
{
    TORRE,
    NOTEBOOK,
    IPAD
} EstiloComputador;

typedef struct computador
{
    float peso;
    EstiloComputador estilo;
    int garantia;
} Computador;

typedef struct programador
{
    int edad;
    Abilidad abilidad;
    Computador *computador;
} Programador;

// Definamos las funciones creadoras y eliminadoras de cada struct:
Computador *create_computador(float peso, EstiloComputador estilo, int garantia)
{
    Computador *computador = malloc(sizeof(Computador));
    computador->peso = peso;
    computador->estilo = estilo;
    computador->garantia = garantia;
    return computador;
}

void delete_computador(Computador *computador)
{
    free(computador);
}

Programador *create_programador(int edad, Abilidad abilidad, float peso, EstiloComputador estilo, int garantia)
{
    Programador *programador = malloc(sizeof(Programador));
    programador->abilidad = abilidad;
    programador->edad = edad;
    programador->computador = create_computador(peso, estilo, garantia);
    return programador;
}

void delete_programador(Programador *programador)
{
    delete_computador(programador->computador);
    free(programador);
}

int main(int argc, char const *argv[])
{
    // Con todo el modelamiento previo que hemos hecho, ahora podemos armar las estrcturas facilmente:

    Programador *programador = create_programador(10, INFINITA, 1.5, TORRE, 1000);
    return 0;
}
