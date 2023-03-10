#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "grafo.h"
#include "vertice.h"
#include "../lista_enc/lista_enc.h"
#include "../lista_enc/no.h"
#include "../arvore/arvore.h"


#define FALSE 0
#define TRUE 1

//#define DEBUG

#define INFINITO INT_MAX

struct grafos
{
    int id;
    lista_enc_t *vertices;
};

//--------------------------------------------------------------------------------------

grafo_t *cria_grafo(int id)
{
    grafo_t *p = NULL;

    p = (grafo_t*) malloc(sizeof(grafo_t));

    if (p == NULL)
    {
        perror("cria_grafo:");
        exit(EXIT_FAILURE);
    }

    p->id = id;
    p->vertices = cria_lista_enc();

    return p;
}

vertice_t* grafo_adicionar_vertice(grafo_t *grafo, char* id)
{
    vertice_t *vertice;
    no_t *no;

#ifdef DEBUG
    printf("grafo_adicionar_vertice: %s\n", id);
#endif

    if (grafo == NULL)
    {
        fprintf(stderr,"grafo_adicionar_vertice: grafo invalido!");
        exit(EXIT_FAILURE);
    }

    if (procura_vertice(grafo, id) != NULL)
    {
        fprintf(stderr,"grafo_adicionar_vertice: vertice duplicado!\n");
        exit(EXIT_FAILURE);
        //printf("voltou\n");
        //return procura_vertice(grafo, id);
    }

    vertice = cria_vertice(id);
    no = cria_no(vertice);

    add_cauda(grafo->vertices, no);

    return vertice;
}

vertice_t* procura_vertice(grafo_t *grafo, char* id)
{
    no_t *no_lista;
    vertice_t *vertice;
    char* meu_id;

    if (grafo == NULL)
    {
        fprintf(stderr,"procura_vertice: grafo invalido!");
        exit(EXIT_FAILURE);
    }

    if (lista_vazia(grafo->vertices) == TRUE)
        return FALSE;

    no_lista = obter_cabeca(grafo->vertices);

    while (no_lista)
    {
        //obtem o endereco da lista
        vertice = obter_dado(no_lista);

        //obterm o id do vertice
        meu_id = vertice_get_id(vertice);
        //printf("%s --- %s \n", meu_id, id);

        if (strcmp(meu_id, id) == 0)
        {
            //printf("%s --- %s --- entrou\n", meu_id, id);
            //printf("entrou\n");
            return vertice;
        }

        no_lista = obtem_proximo(no_lista);
    }

    return NULL;
}

void adiciona_adjacentes(grafo_t *grafo, vertice_t *vertice, int n, ...)
{
    va_list argumentos;
    vertice_t *sucessor;
    arestas_t *aresta;

    int id_sucessor;
    int peso;
    int x;

    /* Initializing arguments to store all values after num */
    va_start (argumentos, n);

    for (x = 0; x < n; x=x+2 )
    {
        id_sucessor = va_arg(argumentos, int);
        peso = va_arg(argumentos, int);

        sucessor = procura_vertice(grafo, id_sucessor);

        if (sucessor == NULL)
        {
            fprintf(stderr, "adiciona_adjacentes: sucessor nao encontrado no grafo\n");
            exit(EXIT_FAILURE);
        }

        aresta = cria_aresta(vertice, sucessor,peso);
        adiciona_aresta(vertice, aresta);

#ifdef DEBUG
        printf("\tvertice: %d\n", vertice_get_id(vertice));
        printf("\tsucessor: %d\n", id_sucessor);
        printf("\tpeso: %d\n", peso);
#endif

    }

    va_end (argumentos);
}

void exportar_grafo_dot(const char *filename, grafo_t *grafo)
{
    FILE *file;

    no_t *no_vert;
    no_t *no_arest;
    vertice_t *vertice;
    vertice_t *adjacente;
    arestas_t *aresta;
    arestas_t *contra_aresta;
    lista_enc_t *lista_arestas;

    int peso;

    if (filename == NULL || grafo == NULL)
    {
        fprintf(stderr, "exportar_grafo_dot: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("exportar_grafp_dot:");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "graph {\n");

    //obtem todos os nos da lista
    no_vert = obter_cabeca(grafo->vertices);
    while (no_vert)
    {
        vertice = obter_dado(no_vert);

        //obtem todos as arestas
        lista_arestas = vertice_get_arestas(vertice);

        no_arest = obter_cabeca(lista_arestas);

        while (no_arest)
        {
            aresta = obter_dado(no_arest);

            //ignora caso j?? exportada
            if (aresta_get_status(aresta) == EXPORTADA)
            {
                no_arest = obtem_proximo(no_arest);
                continue;
            }

            //marca como exportada esta aresta
            aresta_set_status(aresta, EXPORTADA);
            adjacente = aresta_get_adjacente(aresta);

            //marca contra-aresta tamb??m como exporta no caso de grafo n??o direcionados
            //contra_aresta = procurar_adjacente(adjacente, vertice);
            //aresta_set_status(contra_aresta, EXPORTADA);

            //obtem peso
            peso = aresta_get_peso(aresta);

            fprintf(file, "\t%s -- %s [label = %d];\n",
                    vertice_get_id(vertice),
                    vertice_get_id(adjacente),
                    peso);

            no_arest = obtem_proximo(no_arest);
        }
        no_vert = obtem_proximo(no_vert);
    }
    fprintf(file, "}\n");
    fclose(file);
}


void libera_grafo (grafo_t *grafo)
{
    no_t *no_vert;
    no_t *no_arest;
    no_t *no_liberado;
    vertice_t *vertice;
    arestas_t *aresta;
    lista_enc_t *lista_arestas;
    sub_arvore_t *sub_arvore;

    if (grafo == NULL)
    {
        fprintf(stderr, "libera_grafo: grafo invalido\n");
        exit(EXIT_FAILURE);
    }

    //varre todos os vertices
    no_vert = obter_cabeca(grafo->vertices);
    while (no_vert)
    {
        vertice = obter_dado(no_vert);

        //libera todas as arestas
        lista_arestas = vertice_get_arestas(vertice);
        no_arest = obter_cabeca(lista_arestas);
        while (no_arest)
        {
            aresta = obter_dado(no_arest);

            //libera aresta
            free(aresta);

            //libera no da lsita
            no_liberado = no_arest;
            no_arest = obtem_proximo(no_arest);
            free(no_liberado);
        }

        //libera lista de arestas e vertice

        free(vertice_get_id(vertice));
        sub_arvore = vertice_get_sub(vertice);
        free(sub_arvore);
        free(lista_arestas);
        free(vertice);

        //libera no da lista
        no_liberado = no_vert;
        no_vert = obtem_proximo(no_vert);
        free(no_liberado);
    }

    //libera grafo e vertice
    free(grafo->vertices);
    free(grafo);
}

lista_enc_t *passa_vertice(grafo_t *grafo)
{

    if (grafo == NULL)
    {
        fprintf(stderr, "vertice_get_dist: vertice invalido\n");
        exit(EXIT_FAILURE);
    }

    return grafo->vertices;
}

grafo_t *importar_grafo(const char *arquivo, int *numero_arestas){

    char buffer[100];
    int ret, label;
    char *filho, *pai;
    //char filho[5], pai[5];
    grafo_t *grafo;
    arestas_t *aresta;
    vertice_t *elemento_pai;
    vertice_t *elemento_filho;

    filho= malloc(sizeof(char));
    pai= malloc(sizeof(char));
    if (arquivo == NULL){
        fprintf(stderr, "importar_grafo_dot: ponteiros inv??lidos\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL){
        perror("importar_grafo_dot:");
        exit(EXIT_FAILURE);
    }

    fgets (buffer, 100, fp); // Joga fora a primeira linha por ser o cabe??alho
    grafo = cria_grafo(1);
    while (fgets(buffer,100,fp)) {
        if (buffer[0] == 125){ //para o programa quando encontrar '}' no arquivo
            break;
        }
        //puts(buffer);
        ret = sscanf(buffer, "%s -- %s [label = %d];", pai, filho, &label);

        if (ret != 3)
        {
            perror("Erro em importar_grafo: sscanf");
            exit(-1);
        }
        //printf("%s -- %s [label = %d]\n", pai, filho, label);

        if ((elemento_pai = procura_vertice(grafo, pai)) == NULL)
        {
            elemento_pai = grafo_adicionar_vertice(grafo, pai);

        }
        if ((elemento_filho = procura_vertice(grafo, filho)) == NULL){
            elemento_filho = grafo_adicionar_vertice(grafo, filho);

        }

        //printf("%s\n", vertice_get_id(elemento_pai));
        //printf("%s\n", vertice_get_id(elemento_filho));

        adiciona_aresta(elemento_pai, cria_aresta(elemento_pai, elemento_filho, label));
        adiciona_aresta(elemento_filho, cria_aresta(elemento_pai, elemento_filho, label));
        ++*numero_arestas;


    }
    fclose(fp);
    return grafo;

}

lista_enc_t *grafo_get_vertices(grafo_t *grafo)
{
	if (grafo == NULL)
	{
		fprintf(stderr, "grafo_get_vertices: grafo invalido!\n");
		exit(EXIT_FAILURE);
	}

	return grafo->vertices;
}
