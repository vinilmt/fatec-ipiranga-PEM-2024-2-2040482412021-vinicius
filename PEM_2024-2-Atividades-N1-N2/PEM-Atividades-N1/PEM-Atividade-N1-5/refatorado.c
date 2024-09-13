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
} Passo; // Para facilitar na manipulação do tabuleiro
const Passo passos[] = {
    {6, 4, 4, 4, "Após jogada #1 das Brancas (Peão do Rei e2 para e4)"},
    {1, 4, 3, 4, "Após jogada #1 das Pretas (Peão do Rei e7 para e5)"},
    {7, 5, 4, 2, "Após jogada #2 das Brancas (Bispo do Rei f1 para c4)"},
    {0, 1, 2, 2, "Após jogada #2 das Pretas (Cavalo da Dama b8 para c6)"},
    {7, 3, 3, 7, "Após jogada #3 das Brancas (Dama d1 para h5)"},
    {0, 6, 2, 5, "Após jogada #3 das Pretas (Cavalo do Rei g8 para f6)"},
    {3, 7, 1, 5, "Após jogada #4 das Brancas (Dama h5 captura Peão f7 - Xeque Mate)"},
}; // Todas as mudanças no tabuleiro

void imprimirTabuleiro(char tabuleiro[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void moverPeca(char tabuleiro[DIM][DIM], int origemI, int origemJ, int destinoI, int destinoJ) {
    tabuleiro[destinoI][destinoJ] = tabuleiro[origemI][origemJ];
    tabuleiro[origemI][origemJ] = '.';
}

int main() {
    // Tabuleiro com as peças na posição inicial
    char tabuleiro[DIM][DIM] = {
        {'t', 'c', 'b', 'd', 'r', 'b', 'c', 't'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'T', 'C', 'B', 'D', 'R', 'B', 'C', 'T'}};

    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);

    // Itera sobre os passos, movendo as peças do tabuleiro e o imprimindo
    for (int i = 0; i < sizeof(passos) / sizeof(Passo); i++) {
        moverPeca(tabuleiro, passos[i].origemI, passos[i].origemJ, passos[i].destinoI, passos[i].destinoJ);
        printf("%s:\n", passos[i].rotulo);
        imprimirTabuleiro(tabuleiro);
    }

    return 0;
}