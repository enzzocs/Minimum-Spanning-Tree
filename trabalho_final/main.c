#include <stdio.h>
#include <stdlib.h>

#include "grafo/grafo.h"

int main()
{
    grafo_t* grafo;

    printf("Oi enzzo\n");

    grafo = importar_grafo("grafo.dot");

    return 0;
}
