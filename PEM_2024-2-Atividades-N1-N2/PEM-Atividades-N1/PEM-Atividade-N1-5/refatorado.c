/*-------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular               *
 *          Prof. Carlos Veríssimo                             *
 *-------------------------------------------------------------*
 * Objetivo do Programa: Modulação do Código Xeque Pastor      *
 * Data - 13/09/2024                                           *
 * Autor: Vinicius Leon Melo Tavares                           *
 *-------------------------------------------------------------*/

#include <stdio.h>
#define DIM 8

typedef struct {
    int origemI;
    int origemJ;
    int destinoI;
    int destinoJ;
    char *rotulo;
} Passo;
const Passo passos[] = {
    {6, 4, 4, 4, "Após jogada #1 das Brancas (Peão do Rei e2 para e4)"},
    {1, 4, 3, 4, "Após jogada #1 das Pretas (Peão do Rei e7 para e5)"},
    {7, 5, 4, 2, "Após jogada #2 das Brancas (Bispo do Rei f1 para c4)"},
    {0, 1, 2, 2, "Após jogada #2 das Pretas (Cavalo da Dama b8 para c6)"},
    {7, 3, 3, 7, "Após jogada #3 das Brancas (Dama d1 para h5)"},
    {0, 6, 2, 5, "Após jogada #3 das Pretas (Cavalo do Rei g8 para f6)"},
    {3, 7, 1, 5, "Após jogada #4 das Brancas (Dama h5 captura Peão f7 - Xeque Mate)"},
};

void imprimirTabuleiro(char vetor[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("%c ", vetor[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void moverPeca(char vetor[DIM][DIM], int origemI, int origemJ, int destinoI, int destinoJ) {
    vetor[destinoI][destinoJ] = vetor[origemI][origemJ];
    vetor[origemI][origemJ] = '.';
}

int main() {
    // tabuleiro com as peças na posição inicial
    char vetor[DIM][DIM] = {
        {'t', 'c', 'b', 'd', 'r', 'b', 'c', 't'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'T', 'C', 'B', 'D', 'R', 'B', 'C', 'T'}};

    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(vetor);

    for (int i = 0; i < sizeof(passos) / sizeof(Passo); i++) {
        moverPeca(vetor, passos[i].origemI, passos[i].origemJ, passos[i].destinoI, passos[i].destinoJ);
        printf("%s:\n", passos[i].rotulo);
        imprimirTabuleiro(vetor);
    }

    return 0;
}