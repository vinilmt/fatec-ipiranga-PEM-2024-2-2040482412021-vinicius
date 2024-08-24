/*--------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular          *
 *          Prof. Carlos Veríssimo                        *
 *--------------------------------------------------------*
 * Objetivo do Programa: Tabuleiro de Xadrez              *
 * Data - 30/08/2024                                      *
 * Autor: Vinicius Leon Melo Tavares                      *
 *--------------------------------------------------------*/

#include <stdio.h>

#define X 0
#define BR 1
#define BD 2
#define BB1 3
#define BB8 4
#define BC1 5
#define BC8 6
#define BT1 7
#define BT8 8
#define BP1 9
#define BP2 10
#define BP3 11
#define BP4 12
#define BP5 13
#define BP6 14
#define BP7 15
#define BP8 16
#define PR -1
#define PD -2
#define PB1 -3
#define PB8 -4
#define PC1 -5
#define PC8 -6
#define PT1 -7
#define PT8 -8
#define PP1 -9
#define PP2 -10
#define PP3 -11
#define PP4 -12
#define PP5 -13
#define PP6 -14
#define PP7 -15
#define PP8 -16

char* displayPiece(char piece);

int main() {
    char board[64] = {
        PT1, PC1, PB1, PD , PR , PB8, PC8, PT8,
        PP1, PP2, PP3, PP4, PP5, PP6, PP7, PP8,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
         X ,  X ,  X ,  X ,  X ,  X ,  X ,  X ,
        BP1, BP2, BP3, BP4, BP5, BP6, BP7, BP8,
        BT1, BC1, BB1, BD , BR , BB8, BC8, BT8,
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%s ", displayPiece(board[i * 8 + j]));
        }
        printf("\n");
    }

    return 0;
}

char* displayPiece(char piece) {
    switch (piece) {
        case X: return " X ";
        case BR: return "BR ";
        case BD: return "BD ";
        case BB1: return "BB1";
        case BB8: return "BB8";
        case BC1: return "BC1";
        case BC8: return "BC8";
        case BT1: return "BT1";
        case BT8: return "BT8";
        case BP1: return "BP1";
        case BP2: return "BP2";
        case BP3: return "BP3";
        case BP4: return "BP4";
        case BP5: return "BP5";
        case BP6: return "BP6";
        case BP7: return "BP7";
        case BP8: return "BP8";
        case PR: return "PR ";
        case PD: return "PD ";
        case PB1: return "PB1";
        case PB8: return "PB8";
        case PC1: return "PC1";
        case PC8: return "PC8";
        case PT1: return "PT1";
        case PT8: return "PT8";
        case PP1: return "PP1";
        case PP2: return "PP2";
        case PP3: return "PP3";
        case PP4: return "PP4";
        case PP5: return "PP5";
        case PP6: return "PP6";
        case PP7: return "PP7";
        case PP8: return "PP8";
        default: return " ? ";
    }
}