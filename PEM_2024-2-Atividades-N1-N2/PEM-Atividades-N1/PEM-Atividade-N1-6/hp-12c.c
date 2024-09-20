/*-----------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular             *
 *          Prof. Carlos Veríssimo                           *
 *-----------------------------------------------------------*
 * Objetivo do Programa: Implementação da Calculadora HP-12C *
 * Data - 20/09/2024                                         *
 * Autor: Vinicius Leon Melo Tavares                         *
 *-----------------------------------------------------------*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 4
#define EXPRESSION_CAPACITY 200

typedef struct {
    int inner[STACK_CAPACITY];
    int len;
} Stack;

// Retorna 0 se suceder, 1 se ultrapassar a capacidade máxima
int stackPush(Stack* stack, int value) {
    if (stack->len >= STACK_CAPACITY) {
        return 1;
    }

    stack->inner[stack->len] = value;
    stack->len++;

    return 0;
}

// Retorna o último valor da pilha (ou apenas 0 se não há)
int stackPop(Stack* stack) {
    if (stack->len <= 0) {
        return 0;
    }

    stack->len--;
    return stack->inner[stack->len];
}

// Retorna 0 se suceder e 1 se falhar
int parseInt(char* s, int* target) {
    *target = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return 1;  // Carácter inválido
        }

        *target = *target * 10 + (s[i] - '0');
    }

    return 0;
}

/*  Retorna 0 se suceder como um número,
    1 se suceder como um operador,
    2 se o token for inválido,
    3 se a pilha já estiver cheia,
    4 se ocorrer divisão por zero       */
int evaluateToken(Stack* stack, char* token) {

    // Verifica se o token é um número e o empurra para a pilha
    int parsedInt;
    if (parseInt(token, &parsedInt) == 0) {
        return (stackPush(stack, parsedInt) == 0) ? 0 : 3;
    }

    // Para ser um operador, o tamanho precisa ser 1
    if (strlen(token) != 1) {
        return 2;
    }

    int result, op1, op2;

    switch (token[0]) {
        case '+':
            result = stackPop(stack) + stackPop(stack);
            break;
        case '-':
            int subtractor = stackPop(stack);
            result = stackPop(stack) - subtractor;
            break;
        case '*':
            result = stackPop(stack) * stackPop(stack);
            break;
        case '/':
            int divider = stackPop(stack);
            if (divider == 0) {
                stackPush(stack, divider); // Coloca de volta na pilha em caso de erro
                return 4;
            }
            result = stackPop(stack) / divider;
            break;
        default:
            return 2;  // Operador inválido
    }

    stackPush(stack, result);
    return 1;
}


int main() {
    Stack stack;
    char expression[EXPRESSION_CAPACITY];

    printf("Instruções:\n");
    printf("- Digite a expressão na Notação Polonesa Inversa para obter o resultado desta;\n");
    printf("- Digite \"Q\" para encerrar o programa.\n");

    while (1) {
        printf(": ");

        fgets(expression, sizeof(expression), stdin);
        char* token = strtok(expression, " \n");
        if (strcmp(token, "Q") == 0) {
            break;
        }

        while (token != NULL) {
            switch (evaluateToken(&stack, token)) {
                case 1: printf("%i\n", stack.inner[stack.len - 1]); break;
                case 2: printf("%s não é um token válido.\n", token); break;
                case 3: printf("Não foi possível empilhar \"%s\", e portanto o processo foi interrompido.\n", token); break;
                case 4: printf("Não é possível dividir por zero.\n"); break;
            }

            token = strtok(NULL, " \n");
        }
    }

    printf("Obrigado por usar nossa Calculadora Fatec-HP12c\n");
    return 0;
}