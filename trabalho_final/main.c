#include <stdio.h>
#include <stdlib.h>

#include "grafo/grafo.h"
#include "arvore/arvore.h"

int main()
{
    grafo_t* grafo;
    arvore_t* arvore;

    grafo = importar_grafo("grafo.txt");

    exportar_grafo_dot("saida_grafo.txt", grafo);

    arvore = minimum_spannin_tree(grafo);

    return 0;
}
