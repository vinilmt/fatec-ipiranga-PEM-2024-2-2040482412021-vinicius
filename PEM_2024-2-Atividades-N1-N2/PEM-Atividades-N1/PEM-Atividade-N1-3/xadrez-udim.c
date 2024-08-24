/*--------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular          *
 *          Prof. Carlos Veríssimo                        *
 *--------------------------------------------------------*
 * Objetivo do Programa: Tabuleiro de Xadrez              *
 * Data - 30/08/2024                                      *
 * Autor: Vinicius Leon Melo Tavares                      *
 *--------------------------------------------------------*/

#include <stdio.h>

int main() {
    char board[64][4] = {
        "PT1", "PC1", "PB1", "PD ", "PR ", "PB8", "PC8", "PT8",
        "PP1", "PP2", "PP3", "PP4", "PP5", "PP6", "PP7", "PP8",
        " X ", " X ", " X ", " X ", " X ", " X ", " X ", " X ",
        " X ", " X ", " X ", " X ", " X ", " X ", " X ", " X ",
        " X ", " X ", " X ", " X ", " X ", " X ", " X ", " X ",
        " X ", " X ", " X ", " X ", " X ", " X ", " X ", " X ",
        "BP1", "BP2", "BP3", "BP4", "BP5", "BP6", "BP7", "BP8",
        "BT1", "BC1", "BB1", "BD ", "BR ", "BB8", "BC8", "BT8",
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%s ", board[i * 8 + j]);
        }
        printf("\n");
    }

    return 0;
}