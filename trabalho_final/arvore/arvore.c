#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "../lista_enc/lista_enc.h"
#include "../grafo/vertice.h"
struct arvore{
    char* id;
    int grau;
    sub_arvore_t *raiz;
    lista_enc_t *sub_arvores;
};

struct sub_arvore{
    int id;
    int dist_pai;
    sub_arvore_t *pai;
    lista_enc_t *sub_arvores;
};

arvore_t *cria_arvore(int id)
{
    arvore_t *p = NULL;

    p = (arvore_t*) malloc(sizeof(arvore_t));

    if (p == NULL)
    {
        perror("cria_arvore:");
        exit(EXIT_FAILURE);
    }

    p->id = id;
    p->sub_arvores = cria_lista_enc();

    return p;
}

sub_arvore_t *cria_sub_arvore(char* id){
    sub_arvore_t *p = NULL;

    p = (sub_arvore_t*) malloc(sizeof(sub_arvore_t));

    if (p == NULL)
    {
        perror("cria_sub_arvore:");
        exit(EXIT_FAILURE);
    }

    p->id= malloc(sizeof(char));
	memset(p->id, '\0', sizeof(p->id));
	strcpy(p->id, id);
    p->sub_arvores = cria_lista_enc();
    p->dist_pai= -1;


    return p;
}

sub_arvore_t *arvore_adicionar_subarvore(arvore_t *arvore, char* id){
    sub_arvore_t *sub_arvore;
    no_t *no;

    sub_arvore = cria_sub_arvore(id);
    no = cria_no(sub_arvore);
    add_cauda(arvore->sub_arvores, no);
    return sub_arvore;
}

void define_pai(arvore_t *arvore, int id_filho, int id_pai){
    no_t *no_filho;
    no_t *no_pai;
    sub_arvore_t *sub_pai;
    sub_arvore_t *sub_filho;

    no_pai = obter_cabeca(arvore->sub_arvores);
    sub_pai = obter_dado(no_pai);
    while(id_pai != sub_pai->id){
        no_pai = obter_cabeca(arvore->sub_arvores);
        sub_pai = obter_dado(no_pai);
    }
    no_filho = no_pai;
    sub_filho = obter_dado(no_filho);
    while(id_filho!= sub_filho->id){
        no_filho = obtem_proximo(no_filho);
        sub_filho = obter_dado(no_filho);
    }
    sub_filho->pai = sub_pai;
    add_cauda(sub_pai->sub_arvores, no_filho);
}


void define_pai_por_ptr(sub_arvore_t *pai, sub_arvore_t *filho, int label){

    no_t * no = cria_no(filho);
    add_cauda(pai->sub_arvores, no);
    filho->pai = pai;
    filho->dist_pai = label;

}


void exportar_arvore_dot(const char *filename, arvore_t *arvore)
{
    FILE *file;

    no_t *no;
    no_t *no_adj;
    sub_arvore_t *sub_arvore;
    sub_arvore_t *sub_arvore_pai;

    if (filename == NULL || arvore == NULL)
    {
        fprintf(stderr, "exportar_arvore_dot: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("exportar_arvore_dot:");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "graph {\n");

    //obtem todos os nos da lista
    no = obter_cabeca(arvore->sub_arvores);
    while (no)
    {
        sub_arvore_pai = obter_dado(no);

        /* Obtem filhos: adjacentes de pai */

        no_adj = obter_cabeca(sub_arvore_pai->sub_arvores);

        while (no_adj){

            sub_arvore = obter_dado(no_adj);

            fprintf(file, "\t%s -- %s;\n", sub_arvore_pai->id, sub_arvore->id);

            no_adj = obtem_proximo(no_adj);

        }
        no = obtem_proximo(no);
    }
    fprintf(file, "}\n");
    fclose(file);
}
arvore_t *minimum_spannin_tree (grafo_t *grafo){
    arvore_t *arvore;
    no_t *no_vert;
    no_t *no_aresta;
    vertice_t *vertice;
    arestas_t *aresta;
    arestas_t* auxiliar;
    sub_arvore_t *pai;
    sub_arvore_t *filho;
    lista_enc_t *lista_arestas;
    arestas_t **lista_arestas_possiveis; //arestas para onde o grafo pode andar para formar a arvore
    int i=0, x=0;
    int j=0, aux;
    arvore = cria_arvore(1);

    lista_arestas_possiveis = malloc(11*sizeof(arestas_t*));

    no_vert = obter_cabeca(grafo_get_vertices(grafo));

    vertice = obter_dado(no_vert);
    pai = arvore_adicionar_subarvore(arvore, vertice_get_id(vertice));
    vertice_set_sub(vertice, pai);

    while(no_vert){
        //vertice = obter_dado(no_vert);
        vertice_set_vist(vertice, 1);
        //printf("teste\n");
        lista_arestas = vertice_get_arestas(vertice);
        no_aresta = obter_cabeca(lista_arestas);

        while (no_aresta){
            aresta = obter_dado(no_aresta);
            //if(vertice_get_vist(aresta_get_dest(aresta))!=1){
            lista_arestas_possiveis[i]= aresta;
            //printf("%d -- %d\n", i, aresta_get_peso(lista_arestas_possiveis[i]));
            //}
            i++;

            no_aresta = obtem_proximo(no_aresta);
        }

        aresta = lista_arestas_possiveis[j];
        aux=0;
        while(j<i-1){
            if(aresta_get_peso(aresta)>aresta_get_peso(lista_arestas_possiveis[j+1])){
                if((vertice_get_vist(aresta_get_dest(aresta))&& vertice_get_vist(aresta_get_fonte(aresta))) == 0){
                    aresta = lista_arestas_possiveis[j+1];
                    aux= j+1;
           //         printf("teste");
                }
            }
           // printf("%d -- %d\n", i, j);
            j++;
        }

        if(vertice_get_vist(aresta_get_fonte(aresta)) == 1 ){
            vertice = aresta_get_dest(aresta);
            filho = arvore_adicionar_subarvore(arvore, vertice_get_id(vertice));
            vertice_set_sub(vertice, filho);
            vertice = aresta_get_fonte(aresta);
            pai = vertice_get_sub(vertice);
            //printf("%s -- %s\n", pai->id, filho->id);
            define_pai_por_ptr(pai, filho, aresta_get_peso(aresta));

            vertice = aresta_get_dest(aresta);
        }

        else {
            vertice = aresta_get_fonte(aresta);
            filho = arvore_adicionar_subarvore(arvore, vertice_get_id(vertice));
            vertice_set_sub(vertice, filho);
            vertice = aresta_get_dest(aresta);
            pai = vertice_get_sub(vertice);
            //printf("%s -- %s", &pai, &filho);
            define_pai_por_ptr(pai, filho, aresta_get_peso(aresta));

            vertice = aresta_get_fonte(aresta);
        }

        while(x<=i-1){
            printf("antes: %d\n", aresta_get_peso(lista_arestas_possiveis[x]));
            x++;
        }

        auxiliar = lista_arestas_possiveis[i-1];
        copia(lista_arestas_possiveis, i-1, aux); //lista_arestas_possiveis[i] = lista_arestas_possiveis[aux];
        copia2(lista_arestas_possiveis, auxiliar, aux); //lista_arestas_possiveis[aux]=auxiliar;

        x=0;
        i= i-1;
        j=0;

        while(x<=i){
            printf("depois: %d\n", aresta_get_peso(lista_arestas_possiveis[x]));
            x++;
        }
        printf("\n");
        x=0;


        no_vert = obtem_proximo(no_vert);
    }
    return arvore;
}
