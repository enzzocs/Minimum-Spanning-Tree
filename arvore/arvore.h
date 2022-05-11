#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include "../grafo/grafo.h"
typedef struct arvore arvore_t;

typedef struct sub_arvore sub_arvore_t;

arvore_t *cria_arvore(int id);

sub_arvore_t *cria_sub_arvore(char* id);

void define_pai(arvore_t *arvore, int id_filho, int id_pai);

void exportar_arvore_dot(const char *filename, arvore_t *arvore);

sub_arvore_t *arvore_adicionar_subarvore(arvore_t *arvore, char* id);

arvore_t *minimum_spannin_tree (grafo_t *grafo, int numero_arestas);

#endif // ARVORE_H_INCLUDED
