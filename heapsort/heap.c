#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void heapsort(int vetor[]){
    int i;
    build_heap(vetor);
    for(i=tam-1; i>1; i--){
        swap(vetor, 0 , i);
        max_heapify(vetor, 0);
    }
}

void build_heap(int vetor[]){
    int i;
    for(i=(tam-1)/2; i>=0; i--)
        max_heapify(vetor, i);
}

void max_heapify(int vetor[], int i){
    int maior, e , d;
    e = esquerda(i);
    d = direita(i);

    if(e <= tam-1 && vetor[e] > vetor[i])
        maior = e;
    else
        maior = i;

    if (d <= tam-1 && vetor[d]>vetor[maior])
        maior = d;

    if (maior != i){
        swap(vetor, i , maior);
        max_heapify(vetor, maior);
    }

}

int esquerda(int i){
    return 2*i+1;
}

int direita(int i){
    return 2*i+2;
}

void swap(int vetor[], int i, int j){
    int aux;
    aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}
