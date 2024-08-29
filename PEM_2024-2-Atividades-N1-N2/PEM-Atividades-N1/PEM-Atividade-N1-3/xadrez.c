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
const char* PIECE_DISPLAY[TOTAL_PIECE_KINDS] = {
    " X ",
    "Bt1", "Bc2", "Bb3", "Bd ", "Br ", "Bb6", "Bc7", "Bt8",
    "Bp1", "Bp2", "Bp3", "Bp4", "Bp5", "Bp6", "Bp7", "Bp8",
    "Pt1", "Pc2", "Pb3", "Pd ", "Pr ", "Pb6", "Pc7", "Pt8",
    "Pp1", "Pp2", "Pp3", "Pp4", "Pp5", "Pp6", "Pp7", "Pp8",
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
        printf(" %d |", i + 1); 
        for (int j = 0; j < DIM; j++) {
            printf(" %s |", PIECE_DISPLAY[board[i * DIM + j]]);
        }
        printf("\n");
        printf("   |     |     |     |     |     |     |     |     |\n");
        printf("   |.....|.....|.....|.....|.....|.....|.....|.....|\n");
    }
    printf("      A     B     C     D     E     F     G     H\n");
    
    return 0;
}