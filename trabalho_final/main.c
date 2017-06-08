#include <stdio.h>
#include <stdlib.h>

#include "grafo/grafo.h"

int main()
{
    grafo_t* grafo;

    grafo = importar_grafo("grafo.txt");

    return 0;
}
