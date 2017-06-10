#include <stdio.h>
#include <stdlib.h>

#include "grafo/grafo.h"

int main()
{
    grafo_t* grafo;

    printf("oi maria\n");
    grafo = importar_grafo("grafo.dot");

    return 0;
}
