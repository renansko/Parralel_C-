#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <windows.h>

#define NTHREADS 8

void insertionSortParallel(int arr[], int n) {
    int i, key, j;

    #pragma omp parallel for private(i, key, j) shared(arr, n)
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        #pragma omp critical
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

int main() {
    double tempo = omp_get_wtime();

    int sorteio[NTHREADS];

    // Preencher o array com valores aleatórios
    srand(GetTickCount());
    for (int i = 0; i < NTHREADS; i++) {
        sorteio[i] = rand() % 100; // Números aleatórios de 0 a 99
    }

    printf("Array não ordenado: \n");
    
    // #pragma omp parallel for 
    // #pragma aqui caso a array inserida seja grande
    for (int i = 0; i < NTHREADS; i++)
        printf("%d ", sorteio[i]);
    printf("\n");

    insertionSortParallel(sorteio, NTHREADS);

    printf("Array ordenado: \n");

    // #pragma omp parallel for 
    // #pragma aqui caso a array inserida seja grande
    for (int i = 0; i < NTHREADS; i++)
        printf("%d ", sorteio[i]);
    printf("\n");

    printf("Tempo %f\n", omp_get_wtime() - tempo);

    return 0;
}