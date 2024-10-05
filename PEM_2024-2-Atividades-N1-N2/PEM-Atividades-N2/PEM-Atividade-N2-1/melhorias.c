/*--------------------------------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular                                        *
 *          Prof. Carlos Veríssimo                              	                    *
 *--------------------------------------------------------------------------------------*
 * Objetivo do Programa: Melhoria da Implementação de Bubble Sort apresentada em aula   *
 * Data - 04/10/2024                                         		                    *
 * Autor: Vinicius Leon Melo Tavares                         		                    *
 *--------------------------------------------------------------------------------------*/

#include <stdio.h>


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

    printf("Array original: \n");
    printNumbers(numbers, length);

    bubbleSort(numbers, length);

    printf("Array ordenado: \n");
    printNumbers(numbers, length);
    
    return 0;
}