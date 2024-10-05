/*-------------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular                     *
 *          Prof. Carlos Veríssimo                              	 *
 *-------------------------------------------------------------------*
 * Objetivo do Programa: Implementação de Bubble Sort                *
 * Data - 27/09/2024                                         		 *
 * Autor: Vinicius Leon Melo Tavares                         		 *
 *-------------------------------------------------------------------*/
 
#include <stdio.h>


void printNumbers(int numbers[], int length) {
    printf("[");
    
    if (length > 0) {
        printf("%d", numbers[0]);
        
        for (int i = 1; i < length; i++) {
            printf(", %d", numbers[i]);        
        }   
    }
    
    printf("]\n");
}

void bubbleSort(int numbers[], int length) {    
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

int main() {    
    int length = -1;
    
    while (length < 0) {
        printf("Insira o tamanho do array: ");
        scanf("%i", &length);

        if (length < 0) {
            printf("O tamanho do array não pode ser negativo.\n");
        }
    }

    int numbers[length];

    printf("Insira os números do array:\n");
    for (int i = 0; i < length; i++) {
        scanf("%i", &numbers[i]);
    }
    
    printf("Estado original: \n");
    printNumbers(numbers, length);

    bubbleSort(numbers, length);
    
    printf("Após ordenação: \n");
    printNumbers(numbers, length);
}