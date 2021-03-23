#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int numero = 13; // Variable definida
    int *pointer; // Variable no definida
    pointer = NULL; // Puedo asignarle un valor mas tarde

}

int *crear_puntero(int num) { // La función devolverá un puntero a int
    // Esta función no será ejecutada, ya que no la llamamos en main

    int *new_num = malloc(sizeof(int)); // Pedimos memoria para 1 número
    *new_num = num; // Le asignamos el valor del numero a lo que apunta el puntero
    return new_num; // Retornamos el puntero creado

}