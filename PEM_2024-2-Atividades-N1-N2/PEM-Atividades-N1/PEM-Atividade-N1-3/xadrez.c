/*--------------------------------------------------------*

* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Carlos Veríssimo                        *
*--------------------------------------------------------*
* Objetivo do Programa: Montar Tabuleiro de Xadrez       *
* Data - 30/08/2024                                      *
* Autor: Vinicius Leon Melo Tavares                      *
*--------------------------------------------------------*/
 
#include <stdio.h>

#define DIM 8

typedef enum {
    X, // Vázio
    BT1, BC2, BB3, BD , BR , BB6, BC7, BT8, // Peças brancas
    BP1, BP2, BP3, BP4, BP5, BP6, BP7, BP8, // Peões brancos
    PT1, PC2, PB3, PD , PR , PB6, PC7, PT8, // Peças pretas
    PP1, PP2, PP3, PP4, PP5, PP6, PP7, PP8, // Peões pretos
    TOTAL_PIECE_KINDS
} PIECE;
const char* PIECE_DISPLAY_ANSI[TOTAL_PIECE_KINDS] = {
    "\033[1;36m X ",
    "\033[1;97mBt1", "\033[1;97mBc2", "\033[1;97mBb3", "\033[1;97mBd ", "\033[1;97mBr ", "\033[1;97mBb6", "\033[1;97mBc7", "\033[1;97mBt8",
    "\033[1;97mBp1", "\033[1;97mBp2", "\033[1;97mBp3", "\033[1;97mBp4", "\033[1;97mBp5", "\033[1;97mBp6", "\033[1;97mBp7", "\033[1;97mBp8",
    "\033[1;38;5;16mPt1", "\033[1;38;5;16mPc2", "\033[1;38;5;16mPb3", "\033[1;38;5;16mPd ", "\033[1;38;5;16mPr ", "\033[1;38;5;16mPb6", "\033[1;38;5;16mPc7", "\033[1;38;5;16mPt8",
    "\033[1;38;5;16mPp1", "\033[1;38;5;16mPp2", "\033[1;38;5;16mPp3", "\033[1;38;5;16mPp4", "\033[1;38;5;16mPp5", "\033[1;38;5;16mPp6", "\033[1;38;5;16mPp7", "\033[1;38;5;16mPp8",
};
 
 
int main() {
    PIECE board[DIM * DIM] = {
        PT1, PC2, PB3, PD , PR , PB6, PC7, PT8,
        PP1, PP2, PP3, PP4, PP5, PP6, PP7, PP8,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
        BP1, BP2, BP3, BP4, BP5, BP6, BP7, BP8,
        BT1, BC2, BB3, BD , BR , BB6, BC7, BT8,
    };
 
    printf("   .................................................\n");
    for (int i = 0; i < DIM; i++) {
        int j;

        printf(" %d |", i + 1);
        for (j = 0; j < DIM; j++) {
            printf("\033[48;5;247m %s \033[0m|", PIECE_DISPLAY_ANSI[board[i * DIM + j]]);
            j++;
            printf("\033[48;5;61m %s \033[0m|", PIECE_DISPLAY_ANSI[board[i * DIM + j]]);
        }
        printf("\n   |");
        for (j = 0; j < DIM; j++) {
            printf("\033[1;48;5;247m     \033[0m|");
            j++;
            printf("\033[1;48;5;61m     \033[0m|");
        }
        printf("\n   |.....|.....|.....|.....|.....|.....|.....|.....|\n");

        i++;

        printf(" %d |", i + 1);
        for (j = 0; j < DIM; j++) {
            printf("\033[1;48;5;61m %s \033[0m|", PIECE_DISPLAY_ANSI[board[i * DIM + j]]);
            j++;
            printf("\033[1;48;5;247m %s \033[0m|", PIECE_DISPLAY_ANSI[board[i * DIM + j]]);
        }
        printf("\n   |");
        for (j = 0; j < DIM; j++) {
            printf("\033[1;48;5;61m     \033[0m|");
            j++;
            printf("\033[1;48;5;247m     \033[0m|");
        }
        printf("\n   |.....|.....|.....|.....|.....|.....|.....|.....|\n");
    }
    printf("      A     B     C     D     E     F     G     H\n");
    
    return 0;
}