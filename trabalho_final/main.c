#include <stdio.h>
#include <stdlib.h>

#include "grafo/grafo.h"
#include "arvore/arvore.h"

int main()
{
    grafo_t* grafo;
    arvore_t* arvore;
    int numero_arestas_adicionadas = 0;

    grafo = importar_grafo("grafo.txt", &numero_arestas_adicionadas);

    printf("numero de arestas eh %d \n", numero_arestas_adicionadas);

    arvore = minimum_spannin_tree(grafo, numero_arestas_adicionadas);

    exportar_arvore_dot("minimum_spanning_tree.txt", arvore);


    libera_grafo(grafo);
    libera_arvore(arvore);

    return 0;
}
