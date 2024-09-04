/*-------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular               *
 *          Prof. Carlos Veríssimo                             *
 *-------------------------------------------------------------*
 * Objetivo do Programa: Implementação da Jogada Xeque Pastor  *
 * Data - 06/09/2024                                           *
 * Autor: Vinicius Leon Melo Tavares                           *
 *-------------------------------------------------------------*/
 
#include <stdio.h>

#define DIM 8 // Dimensão do tabuleiro

#define WHITE "\e[1;97m" // Cor para peças brancas
#define BLACK "\e[1;38;5;16m" // Cor para peças pretas
#define NEUTRAL "\e[1;33m" // Cor para legendas
#define BACKGROUND_LIGHT "\e[105m" // Cor de fundo primária
#define BACKGROUND_DARK "\e[45m" // Cor de fundo secundária
#define RESET "\e[0m" // Resetar todos os atributos ANSI para o padrão

// Cada estado do enum está associado a um valor númerico, a partir de 0
typedef enum {
    X, // Vazio
    WHITE_TRAIL, // Rastro de peça branca
    BLACK_TRAIL, // Rastro de peça preta
    BT1, BC1, BB1, BD1, BR1, BB2, BC2, BT2, // Peças brancas
    BP1, BP2, BP3, BP4, BP5, BP6, BP7, BP8, // Peões brancos
    PT1, PC1, PB1, PD1, PR1, PB2, PC2, PT2, // Peças pretas
    PP1, PP2, PP3, PP4, PP5, PP6, PP7, PP8, // Peões pretos
    TOTAL_PIECE_KINDS // Esse estado extra corresponde ao total de estados (exceto este)
} PIECE;
typedef enum { OK, ERR } STATUS; // A função retorna isso quando pode falhar

typedef struct { int value; STATUS status; } ResultInt; // Quando retorna um valor inteiro mas pode falhar

// Representação ANSI de cada peça, acessada através de índice (o valor associado aos estados do enum)
const char* PIECE_DISPLAY_ANSI[TOTAL_PIECE_KINDS] = {
    "   ",
    WHITE "...",
    BLACK "...",
    WHITE "Bt1", WHITE "Bc1", WHITE "Bb1", WHITE "Bd1", WHITE "Br1", WHITE "Bb2", WHITE "Bc2", WHITE "Bt2",
    WHITE "Bp1", WHITE "Bp2", WHITE "Bp3", WHITE "Bp4", WHITE "Bp5", WHITE "Bp6", WHITE "Bp7", WHITE "Bp8",
    BLACK "Pt1", BLACK "Pc1", BLACK "Pb1", BLACK "Pd1", BLACK "Pr1", BLACK "Pb2", BLACK "Pc2", BLACK "Pt2",
    BLACK "Pp1", BLACK "Pp2", BLACK "Pp3", BLACK "Pp4", BLACK "Pp5", BLACK "Pp6", BLACK "Pp7", BLACK "Pp8",
};

void displayBoard(PIECE* board);
ResultInt convertCoordinatesToIndex(char* coord);
void whiteMoveTo(PIECE* board, int from, int to);
void blackMoveTo(PIECE* board, int from, int to);
void clearPosition(PIECE* board, int index);

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
    
    printf(NEUTRAL "\n              INÍCIO DA PARTIDA\n\n" RESET);
    displayBoard(board);
    printf("\n");

    const char fromSequence[7][2] = {"e2", "e7", "f1", "b8", "d1", "g8", "h5"};
    const char toSequence[7][2] = {"e4", "e5", "c4", "c6", "h5", "f6", "f7"};
    const char* labels[7] = {
        "Brancas jogam e4",
        "Pretas jogam e5",
        "Brancas jogam Bc4",
        "Pretas jogam Cc6",
        "Brancas jogam Dh5",
        "Pretas jogam Cf6",
        "Brancas capturam Peão, Xeque Mate: Dxf7#"
    };

    // Como os rastros são limpos apenas após a jogada de ambos
    // é necessário guardar o índice do rastro da peça branca
    int formerWhiteFrom;

    for (int i = 0; i < 7; i++) {
        ResultInt from = convertCoordinatesToIndex(fromSequence[i]);
        ResultInt to = convertCoordinatesToIndex(toSequence[i]);
        if (i % 2 == 0) {
            formerWhiteFrom = from.value;
            whiteMoveTo(board, from.value, to.value);
            printf(
                NEUTRAL "\n                  JOGADA #%d\n\n   %s\n" RESET,
                i / 2 + 1,
                labels[i]
            );
            displayBoard(board);
            printf("\n");
        } else {
            blackMoveTo(board, from.value, to.value);
            printf(NEUTRAL "   %s\n" RESET, labels[i]);
            displayBoard(board);
            printf("\n");

            clearPosition(board, formerWhiteFrom);
            clearPosition(board, from.value);
        }
    }

    return 0;
}

void displayBoard(PIECE* board) {
    char* bg_1;
    char* bg_2;

    for (int i = 0; i < DIM; i++) {
        // Inverte a ordem das cores de fundo a cada linha
        if (i % 2 == 0) {
            bg_1 = BACKGROUND_LIGHT;
            bg_2 = BACKGROUND_DARK;
        } else {
            bg_1 = BACKGROUND_DARK;
            bg_2 = BACKGROUND_LIGHT;
        }
    
        printf(NEUTRAL " %d " RESET, 8 - i);
        for (int j = 0; j < DIM; j++) {
            char* bg = (j % 2 == 0) ? bg_1 : bg_2; // Alterna a cor de fundo a cada espaço
            printf("%s %s " RESET, bg, PIECE_DISPLAY_ANSI[board[i * DIM + j]]);
        }
        printf("\n   ");
        for (int j = 0; j < DIM; j++) {
            char* bg = (j % 2 == 0) ? bg_1 : bg_2; // Alterna a cor de fundo a cada espaço
            printf("%s     " RESET, bg);
        }
        printf("\n");
    }
    printf(NEUTRAL "     A    B    C    D    E    F    G    H\n" RESET);
}

ResultInt convertCoordinatesToIndex(char* coord) {
    int X, Y;
    ResultInt result;

    // coord deve haver ao menos dois caracteres, senão comporrtamento indefinido
    switch (coord[0]) {
        case 'a': X = 0; break;
        case 'b': X = 1; break;
        case 'c': X = 2; break;
        case 'd': X = 3; break;
        case 'e': X = 4; break;
        case 'f': X = 5; break;
        case 'g': X = 6; break;
        case 'h': X = 7; break;
        default:
            result.status = ERR;
            return result;
    }
    switch (coord[1]) {
        case '1': Y = 7; break;
        case '2': Y = 6; break;
        case '3': Y = 5; break;
        case '4': Y = 4; break;
        case '5': Y = 3; break;
        case '6': Y = 2; break;
        case '7': Y = 1; break;
        case '8': Y = 0; break;
        default:
            result.status = ERR;
            return result;
    }

    result.value = Y * DIM + X;
    result.status = OK;
    return result;
}

void whiteMoveTo(PIECE* board, int from, int to) {
    // Deve existir estes índices dentro de board, senão comportamento indefinido
    PIECE piece = board[from];
    board[from] = WHITE_TRAIL;
    board[to] = piece;
}

void blackMoveTo(PIECE* board, int from, int to) {
    // Deve existir estes índices dentro de board, senão comportamento indefinido
    PIECE piece = board[from];
    board[from] = BLACK_TRAIL;
    board[to] = piece;
}

void clearPosition(PIECE* board, int index) {
    // Deve existir este índice dentro de board, senão comportamento indefinido
    board[index] = X;
}