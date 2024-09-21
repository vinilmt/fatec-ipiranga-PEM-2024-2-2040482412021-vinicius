/*-----------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular             *
 *          Prof. Carlos Veríssimo                           *
 *-----------------------------------------------------------*
 * Objetivo do Programa: Implementação da Calculadora HP-12C *
 * Data - 20/09/2024                                         *
 * Autor: Vinicius Leon Melo Tavares                         *
 *-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 4
#define INPUT_CAPACITY 200

typedef enum { Ok, Error } Status;
typedef enum {
    NumberOk,
    OperatorOk,
    InvalidTokenError,
    StackIsFullError,
    DivideByZeroError
} EvaluateTokenStatus;
typedef struct {
    int inner[STACK_CAPACITY];
    int len;
} Stack;

// Retorna Error se a pilha estiver cheia
Status stackPush(Stack* stack, int value) {
    if (stack->len >= STACK_CAPACITY) {
        return Error;
    }

    stack->inner[stack->len] = value;
    stack->len++;

    return Ok;
}

// Retorna Error se a pilha estiver vazia
Status stackPop(Stack* stack, int* target) {
    if (stack->len <= 0) {
        return Error;
    }

    stack->len--;
    *target = stack->inner[stack->len];

    return Ok;
}

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

EvaluateTokenStatus evaluateToken(Stack* stack, char* token) {
    // Verifica se o token é um número e o empurra para a pilha
    int parsedInt;
    if (parseInt(token, &parsedInt) == Ok) {
        return (stackPush(stack, parsedInt) == Ok) ? NumberOk : StackIsFullError;
    }

    // Para ser um operador, o tamanho precisa ser 1
    if (strlen(token) != 1) {
        return InvalidTokenError;
    }

    int result, value1 = 0, value2 = 0;

    switch (token[0]) {
        case '+':
            stackPop(stack, &value2); stackPop(stack, &value1);
            result = value1 + value2;
            break;
        case '-':
            stackPop(stack, &value2); stackPop(stack, &value1);
            result = value1 - value2;
            break;
        case '*':
            stackPop(stack, &value2); stackPop(stack, &value1);
            result = value1 * value2;
            break;
        case '/':
            stackPop(stack, &value2);
            if (value2 == 0) {
                stackPush(stack, value2); // Coloca de volta na pilha em caso de erro
                return DivideByZeroError;
            }
            stackPop(stack, &value1);
            result = value1 / value2;
            break;
        default:
            return InvalidTokenError;  // Operador inválido
    }

    stackPush(stack, result);
    return OperatorOk;
}


int main() {
    Stack stack = {0};
    char input[INPUT_CAPACITY] = {0};

    printf("Instruções:\n");
    printf("- Digite a expressão na Notação Polonesa Inversa para obter o resultado desta;\n");
    printf("- Digite \"Q\" para encerrar o programa.\n");

    while (1) {
        printf(": ");

        fgets(input, INPUT_CAPACITY, stdin);
        
        char* token = strtok(input, " \n");

        if (token == NULL) {
            continue;
        }

        if (strcmp(token, "Q") == 0) {
            break;
        }

        while (token != NULL) {
            switch (evaluateToken(&stack, token)) {
                case NumberOk: break;
                case OperatorOk: printf("%i\n", stack.inner[stack.len - 1]); break;
                case InvalidTokenError: printf("\"%s\" não é um token válido.\n", token); break;
                case StackIsFullError: printf("Não foi possível empilhar \"%s\", e portanto o processo foi interrompido.\n", token); break;
                case DivideByZeroError: printf("Não é possível dividir por zero.\n"); break;
            }

            token = strtok(NULL, " \n");
        }
    }

    printf("Obrigado por usar nossa Calculadora Fatec-HP12c\n");
    return 0;
}