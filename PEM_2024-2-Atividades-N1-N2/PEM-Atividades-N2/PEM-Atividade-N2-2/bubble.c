/*----------------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular                        *
 *          Prof. Carlos Veríssimo                              	    *
 *----------------------------------------------------------------------*
 * Objetivo do Programa: Comparação entre Bubble Sort e Insertion Sort  *
 * Data - 11/10/2024                                         		    *
 * Autor: Vinicius Leon Melo Tavares                		            *
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int cycles_amount;
    int swaps_amount;
    double cpu_time_used;
} Tracker;

Tracker trackedBubbleSort(int numbers[], int length) {    
    Tracker tracker = {0};

    clock_t start = clock();

    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;

                tracker.swaps_amount++;
            }
        }

        tracker.cycles_amount++;
    }

    clock_t end = clock();
    tracker.cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    return tracker;
}

int main() {
    int numbers[] = {
        5, 3, 8, 4, 2,
        115, 113, 118, 114, 112,
        125, 123, 128, 124, 122,
        35, 33, 38, 34, 32,
        45, 43, 48, 44, 42,
        55, 53, 58, 54, 52,
        65, 63, 68, 64, 62,
        75, 73, 78, 74, 72,
        85, 83, 88, 84, 82,
        95, 93, 98, 94, 92,
        15, 13, 18, 14, 12,
        25, 23, 28, 24, 22
    };
    
    Tracker tracker = trackedBubbleSort(numbers, sizeof(numbers) / sizeof(int));
    
    printf("Quantidade de ciclos: %i\n", tracker.cycles_amount);
    printf("Quantidade de trocas: %i\n", tracker.swaps_amount);
    printf("Tempo de execução: %f segundos\n", tracker.cpu_time_used);

    return 0;
}