#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {

    for (int i = 0; i < 5; i++) { // Iteramos 5 veces, con valores de i que aumentan de a uno

        printf("Iteración número %d\n", i + 1); // Imprimimos i + 1 usando %d
        // fprintf(stdout, "Iteración número %d\n", i + 1); // Es lo mismo

    };

    if (true) {

        prtinf("Esto siempre se imprime :D\n");

    } else if (false) {

        printf("Esto nunca se imprime :c\n");

    } else {

        printf("Esto tampoco :'c\n");

    };

}