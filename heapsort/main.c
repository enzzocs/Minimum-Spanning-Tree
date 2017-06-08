#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main()
{
    int vetor[tam] = {14, 2, 9, 1, 16, 7, 3, 10, 4, 8};
    int i;
    heapsort(vetor);
    for (i=0; i<=tam-1; i++){
        printf("%d, ", vetor[i]);
    }

    return 0;
}
