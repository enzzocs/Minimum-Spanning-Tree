#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"

struct lista_enc{
    no_t *cabeca;
    no_t *cauda;
    int tamanho;
};

struct no{
    void *dados;
    no_t *proximo;
    no_t *anterior;
};

lista_enc_t *cria_lista_enc (void) {
    lista_enc_t *p = malloc(sizeof(lista_enc_t));

    if (p == NULL){
        perror("cria_lista_enc:");
        exit(EXIT_FAILURE);
    }

    p->cabeca = NULL;
    p->cauda = NULL;
    p->tamanho = 0;

    return p;
}


