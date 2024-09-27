/*-------------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular                     *
 *          Prof. Carlos Veríssimo                              	 *
 *-------------------------------------------------------------------*
 * Objetivo do Programa: Implementação de Bubble Sort                *
 * Data - 27/09/2024                                         		 *
 * Autor: Vinicius Leon Melo Tavares                         		 *
 *-------------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_CAPACITY 200
#define ARRAY_CAPACITY 50

typedef enum { Ok, Error } Status;

// Retorna Error se houver um carácter inválido
Status parseInt(char* s, int* target) {
    *target = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return Error;
        }

        *target = *target * 10 + (s[i] - '0');
    }

    return Ok;
}

void printNumbers(int numbers[ARRAY_CAPACITY], size_t length) {
    printf("[");
    
    if (length > 0) {
        printf("%d", numbers[0]);
        
        for (int i = 1; i < length; i++) {
            printf(", %d", numbers[i]);        
        }   
    }
    
    printf("]");
}

void bubbleSort(int numbers[ARRAY_CAPACITY], size_t length) {
    if (length == 0) {
        return;
    }
    
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
    char input[INPUT_BUFFER_CAPACITY] = {0};
    
    printf("Insira os números: ");
    fgets(input, INPUT_BUFFER_CAPACITY, stdin);
    char* token = strtok(input, " \n");
    
    int numbers[ARRAY_CAPACITY];
    size_t length = 0;

    while (token != NULL) {
        if (length >= ARRAY_CAPACITY) {
            printf(
                "A entrada de números foi truncada, pois a capacidade máxima do array é %d elementos.\n",
                ARRAY_CAPACITY
            );
            break;
        }
        
        int parsedInt;
        if (parseInt(token, &parsedInt) == Error) {
            printf("O token \"%s\" é inválido.", token);
            return 1;
        }
        
        numbers[length] = parsedInt;
        length += 1;
        
        token = strtok(NULL, " \n");
    };
    
    printf("Estado original: \n");
    printNumbers(numbers, length);
    printf("\n");
    
    bubbleSort(numbers, length);
    
    printf("Após ordenação: \n");
    printNumbers(numbers, length);
}