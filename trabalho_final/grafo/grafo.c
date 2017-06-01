#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "../lista_enc/lista_enc.h"

struct grafos{
    int id;
    lista_enc_t *vertices;
};

grafo_t *importar_grafo(const char *arquivo, grafo_t *grafo){

    char buffer[100];
    int ret, pai, filho;
    no_t *elemento;


    if (arquivo == NULL || grafo ==NULL){
        fprintf(stderr, "importar_grafo_dot: ponteiros inválidos\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL){
        perror("exportar_grafp_dot:");
        exit(EXIT_FAILURE);
    }

    fgets (buffer, 100, fp); // Joga fora a primeira linha por ser o cabeçalho
    grafo = cria_lista_enc();
    while (fgets(buffer,100,fp)!= '}') {
        ret = sscanf(buffer, "%d -- %d", &pai, &filho);
        if (ret != 3)
        {
            perror("Erro em main: fscanf");
            exit(-1);
        }

//        elemento = cria_no(cria_vertice(pai, filho));
//        add_cauda(grafo, elemento);

    }
    fclose(fp);
    return grafo;

}
