#include <stdio.h>

// Para compilar este código puedes utilizar el comando gcc -o exe sintaxis.c

int main(int argc, char const *argv[])
{
    // Debemos declarar todo los tipos de nuestras variables
    int numero = 5;
    char caracter = 'j'; // Los caracteres DEBEN tener COMILLAS SIMPLES, no es valido 'esto'.
    float pi = 3.14;

    // Tanto while como for como if deben tener su cuerpo entre corchetes.
    int i = 1;
    printf("Contando hasta 3 con while: ");
    while (i < 4)
    {
        printf("%d ", i++);
    }
    printf("\n");

    // Recuerden la nomenclatura del for
    printf("Contando hasta 3 con for: ");
    for (int contador = 1; contador < 4; contador++)
    {
        printf("%d ", contador);
    }
    printf("\n");

    // Ejempllo de uso de if
    int promedio = 4;
    if (numero < 4)
    {
        printf("Te echaste SSOO y Redes :-(\n");
    }
    else if (numero == 4)
    {
        printf("Pasaste SSOO y Redes :-)!\n");
    }
    else
    {
        printf("Felcidades!\n");
    }

    /* Cosas a considerar
    * 1. printf no incluye automaticamente el salto de linea, hay que ponerlo explicito.
    * 2. recuerden los ;.
    * 3. recuerden incluir los archivos necesarios si quieren utilizar printf/malloc/etc.
    * */

    return 0;
}
