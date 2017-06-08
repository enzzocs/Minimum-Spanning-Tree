#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"
#include "../lista_enc/lista_enc.h"

struct arvore{
    int id;
    int grau;
    sub_arvore_t *raiz;
    lista_enc_t *sub_arvores;
};

struct sub_arvore{
    int id;
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

sub_arvore_t *cria_sub_arvore(int id){
    sub_arvore_t *p = NULL;

    p = (sub_arvore_t*) malloc(sizeof(sub_arvore_t));

    if (p == NULL)
    {
        perror("cria_sub_arvore:");
        exit(EXIT_FAILURE);
    }

    p->id = id;
    p->sub_arvores = cria_lista_enc();


    return p;
}

sub_arvore_t *arvore_adicionar_subarvore(arvore_t *arvore, int id){
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


void define_pai_por_ptr(sub_arvore_t *pai, sub_arvore_t *filho){

    no_t * no = cria_no(filho);
    add_cauda(pai->sub_arvores, no);
    filho->pai = pai;

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

            fprintf(file, "\t%d -- %d;\n", sub_arvore_pai->id, sub_arvore->id);

            no_adj = obtem_proximo(no_adj);

        }
        no = obtem_proximo(no);
    }
    fprintf(file, "}\n");
    fclose(file);
}
