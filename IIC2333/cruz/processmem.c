#include <stdio.h>
#include <stdlib.h>

/* Todo el código está en .text */

/* Todo esto va en .data */
char arregloGlobalEnData[1000];
int m[100];
int g = 2020;

struct z {
    int a;
    int b[500];
} unstruct;

int func(int c, int d) {

	int arregloLocal[50];    // también está en el stack de func
    printf("[func] Variables del stack:\n");
    printf("[func] d:                 %p\n", &d);
	printf("[func] c:                 %p\n", &c);
	printf("[func] arregloLocal:      %p\n", arregloLocal);
	return c + d;            // al retornar se pierde arregloLocal

}

int* dameMemoria(int bytes) {

    int a = 1;
    int b = 2;
    int arregloLocal[50];    // 50 * sizeof(int) bytes en el stack

    /* Puntero está en el stack. Memoria asignado se crean en heap */
    int* punteroConMemoria = (int*) malloc(sizeof(int)*bytes);
    punteroConMemoria[20] = 42; // este contenido va en el heap
    int* punteroQueSeraLiberado = (int*) malloc(sizeof(int)*bytes*2);

    for(int i=0; i<50; i++) {
    	arregloLocal[i] = i*bytes;
    }

    printf("[dameMemoria] Variables del stack:\n");
	printf("[dameMemoria] a:                      %p\n", &a);
	printf("[dameMemoria] b:                      %p\n", &b);
	printf("[dameMemoria] arregloLocal:           %p\n", arregloLocal);
	printf("[dameMemoria] punteroConMemoria:      %p\n", &punteroConMemoria);
    printf("[dameMemoria] punteroQueSeraLiberado: %p\n", &punteroConMemoria);

    printf("[dameMemoria] Memoria en el heap:\n");
    printf("[dameMemoria] punteroConMemoria:      %p\n", punteroConMemoria);
    printf("[dameMemoria] punteroQueSeraLiberado: %p\n", punteroQueSeraLiberado);

    free(punteroQueSeraLiberado);
    /* Al retornar se elimina "punteroConMemoria", pero no su memoria */
    /* Si no se hace free, la memoria queda en el heap y no la puedo acceder más */
    /* A menos que retorne su dirección */
    return punteroConMemoria;
}


int main() {

    int arregloEnStack[10];     // esto se crean el stack de main
    int* punteroSinMemoria;     // esto también
    int a = 5; 
    int b;   

	printf("Hello World\n");
	printf("Calling a function ... ");

	b = func(a, 37);
    printf("Resultado de func: %d\n", b);

    printf("Variables en .data:\n");
	printf("g:                      %p\n", &g);
	printf("m:                      %p\n", m);
	printf("arregloGlobalEnData:    %p\n", arregloGlobalEnData);
    printf("struct:                 %p\n\n", &unstruct);

    printf("Variables en el stack de main:\n");
	printf("arregloEnStack:         %p\n", arregloEnStack);	
	printf("punteroSinMemoria:      %p\n", &punteroSinMemoria);	
	printf("a:                      %p\n", &a);
	printf("b:                      %p\n\n", &b);


	printf("punteroSinMemoria:      %p\n", punteroSinMemoria);	
	printf("Pidiendo memoria ...\n");
    punteroSinMemoria = dameMemoria(100);
	printf("punteroSinMemoria:      %p\n", punteroSinMemoria);	

    printf("No me quiero iiiiiiirrrr.... ");
    scanf("%d\n", &a);

	/* Antes de terminar debo liberar la memoria que pedí,
	   aún si eso ocurrió en otra función */
	free(punteroSinMemoria);

	return 0;
}