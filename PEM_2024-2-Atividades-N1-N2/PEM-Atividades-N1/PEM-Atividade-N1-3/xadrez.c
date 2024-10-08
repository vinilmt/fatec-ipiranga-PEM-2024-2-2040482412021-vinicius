/*--------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular          *
 *          Prof. Carlos Veríssimo                        *
 *--------------------------------------------------------*
 * Objetivo do Programa: Montar Tabuleiro de Xadrez       *
 * Data - 30/08/2024                                      *
 * Autor: Vinicius Leon Melo Tavares                      *
 *--------------------------------------------------------*/
 
#include <stdio.h>

#define DIM 8 // Dimensão do tabuleiro

#define ESC "\033" // ANSI Escape 
#define WHITE "[1;97m" // Cor para peças brancas
#define BLACK "[1;38;5;16m" // Cor para peças pretas
#define NEUTRAL "[1;33m" // Cor para espaço vazio
#define BACKGROUND_LIGHT "[48;5;163m" // Cor de fundo primária
#define BACKGROUND_DARK "[48;5;57m" // Cor de fundo secundária
#define RESET "[0m" // Resetar todos os atributos ANSI para o padrão

// Cada estado do enum está associado a um valor númerico, a partir de 0
typedef enum {
    X, // Vazio
    BT1, BC1, BB1, BD1, BR1, BB2, BC2, BT2, // Peças brancas
    BP1, BP2, BP3, BP4, BP5, BP6, BP7, BP8, // Peões brancos
    PT1, PC1, PB1, PD1, PR1, PB2, PC2, PT2, // Peças pretas
    PP1, PP2, PP3, PP4, PP5, PP6, PP7, PP8, // Peões pretos
    TOTAL_PIECE_KINDS // Esse estado extra corresponde ao total de estados (exceto este)
} PIECE;

// Representação ANSI de cada peça, acessada através de índice (o valor associado aos estados do enum)
const char* PIECE_DISPLAY_ANSI[TOTAL_PIECE_KINDS] = {
    ESC NEUTRAL " X ",
    ESC WHITE "Bt1", ESC WHITE "Bc1", ESC WHITE "Bb1", ESC WHITE "Bd1", ESC WHITE "Br1", ESC WHITE "Bb2", ESC WHITE "Bc2", ESC WHITE "Bt2",
    ESC WHITE "Bp1", ESC WHITE "Bp2", ESC WHITE "Bp3", ESC WHITE "Bp4", ESC WHITE "Bp5", ESC WHITE "Bp6", ESC WHITE "Bp7", ESC WHITE "Bp8",
    ESC BLACK "Pt1", ESC BLACK "Pc1", ESC BLACK "Pb1", ESC BLACK "Pd1", ESC BLACK "Pr1", ESC BLACK "Pb2", ESC BLACK "Pc2", ESC BLACK "Pt2",
    ESC BLACK "Pp1", ESC BLACK "Pp2", ESC BLACK "Pp3", ESC BLACK "Pp4", ESC BLACK "Pp5", ESC BLACK "Pp6", ESC BLACK "Pp7", ESC BLACK "Pp8",
};
 
int main() {
    PIECE board[DIM * DIM] = {
        PT1, PC1, PB1, PD1, PR1, PB2, PC2, PT2,
        PP1, PP2, PP3, PP4, PP5, PP6, PP7, PP8,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
        BP1, BP2, BP3, BP4, BP5, BP6, BP7, BP8,
        BT1, BC1, BB1, BD1, BR1, BB2, BC2, BT2,
    };
 
    char* bg_1;
    char* bg_2;

    printf("   .................................................\n");
    for (int i = 0; i < DIM; i++) {
        // Inverte a ordem das cores de fundo a cada linha
        if (i % 2 == 0) {
            bg_1 = BACKGROUND_LIGHT;
            bg_2 = BACKGROUND_DARK;
        } else {
            bg_1 = BACKGROUND_DARK;
            bg_2 = BACKGROUND_LIGHT;
        }
    
        printf(" %d |", 8 - i);
        for (int j = 0; j < DIM; j++) {
            char* bg = (j % 2 == 0) ? bg_1 : bg_2; // Alterna a cor de fundo a cada espaço
            printf(ESC "%s %s " ESC RESET "|", bg, PIECE_DISPLAY_ANSI[board[i * DIM + j]]);
        }
        printf("\n   |");
        for (int j = 0; j < DIM; j++) {
            char* bg = (j % 2 == 0) ? bg_1 : bg_2; // Alterna a cor de fundo a cada espaço
            printf(ESC "%s     " ESC RESET "|", bg);
        }
        printf("\n   |.....|.....|.....|.....|.....|.....|.....|.....|\n");
    }
    printf("      A     B     C     D     E     F     G     H\n");
    
    return 0;
}