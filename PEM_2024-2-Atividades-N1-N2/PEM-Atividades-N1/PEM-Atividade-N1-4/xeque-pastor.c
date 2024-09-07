/*-------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular               *
 *          Prof. Carlos Veríssimo                             *
 *-------------------------------------------------------------*
 * Objetivo do Programa: Implementação da Jogada xeque Pastor  *
 * Data - 06/09/2024                                           *
 * Autor: Vinicius Leon Melo Tavares                           *
 *-------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdbool.h>

#define DIM 8 // Dimensão do tabuleiro

#define WHITE "\e[1;97m" // Cor para peças brancas
#define BLACK "\e[1;38;5;16m" // Cor para peças pretas
#define NEUTRAL "\e[1;33m" // Cor para legendas
#define BACKGROUND_LIGHT "\e[105m" // Cor de fundo primária
#define BACKGROUND_DARK "\e[45m" // Cor de fundo secundária
#define RESET "\e[0m" // Resetar todos os atributos ANSI para o padrão

// Cada estado do enum está associado a um valor númerico, a partir de 0
typedef enum {
    Empty, // Vazio
    WhiteTrail, // Rastro de peça branca
    BlackTrail, // Rastro de peça preta
    Bt1, Bc1, Bb1, Bd1, Br1, Bb2, Bc2, Bt2, // Peças brancas
    Bp1, Bp2, Bp3, Bp4, Bp5, Bp6, Bp7, Bp8, // Peões brancos
    Pt1, Pc1, Pb1, Pd1, Pr1, Pb2, Pc2, Pt2, // Peças pretas
    Pp1, Pp2, Pp3, Pp4, Pp5, Pp6, Pp7, Pp8, // Peões pretos
} Slot;
typedef enum { Ok, Err } Status; // A função retorna isso quando pode falhar
typedef enum { White, Black } Color; // Irá alternar entre um e outro durante o jogo para comportamentos específicos

// Representação ANSI de cada peça, acessada através de índice (o valor associado aos estados do enum)
const char* SLOT_DISPLAY_ANSI[] = {
    "   ",
    WHITE "...",
    BLACK "...",
    WHITE "Bt1", WHITE "Bc1", WHITE "Bb1", WHITE "Bd1", WHITE "Br1", WHITE "Bb2", WHITE "Bc2", WHITE "Bt2",
    WHITE "Bp1", WHITE "Bp2", WHITE "Bp3", WHITE "Bp4", WHITE "Bp5", WHITE "Bp6", WHITE "Bp7", WHITE "Bp8",
    BLACK "Pt1", BLACK "Pc1", BLACK "Pb1", BLACK "Pd1", BLACK "Pr1", BLACK "Pb2", BLACK "Pc2", BLACK "Pt2",
    BLACK "Pp1", BLACK "Pp2", BLACK "Pp3", BLACK "Pp4", BLACK "Pp5", BLACK "Pp6", BLACK "Pp7", BLACK "Pp8",
};

void printBoard(Slot board[][DIM]) {
    char* backgroundPattern[2] = {BACKGROUND_LIGHT, BACKGROUND_DARK};
    int patternIndex = 0;

    for (int i = 0; i < DIM; i++) {
        printf(NEUTRAL " %d " RESET, 8 - i);

        for (int j = 0; j < DIM; j++) {
            char* bg = backgroundPattern[patternIndex];
            patternIndex = 1 - patternIndex; // Alterna a cor de fundo a cada espaço
            printf("%s %s " RESET, bg, SLOT_DISPLAY_ANSI[board[i][j]]);
        }
        printf("\n   ");

        // Gera a área vazia em baixo de cada espaço
        for (int j = 0; j < DIM; j++) {
            char* bg = backgroundPattern[patternIndex];
            patternIndex = 1 - patternIndex; // Alterna a cor de fundo a cada espaço
            printf("%s     " RESET, bg);
        }
        printf("\n");

        patternIndex = 1 - patternIndex; // Alterna a ordem das cores de fundo a cada linha
    }

    printf(NEUTRAL "     A    B    C    D    E    F    G    H\n" RESET);
}

Status deducePositionFromRaw(char rawX, char rawY, int* column, int* row) {
    switch (rawX) {
        case 'a': *column = 0; break;
        case 'b': *column = 1; break;
        case 'c': *column = 2; break;
        case 'd': *column = 3; break;
        case 'e': *column = 4; break;
        case 'f': *column = 5; break;
        case 'g': *column = 6; break;
        case 'h': *column = 7; break;
        default: return Err;
    }
    switch (rawY) {
        case '1': *row = 7; break;
        case '2': *row = 6; break;
        case '3': *row = 5; break;
        case '4': *row = 4; break;
        case '5': *row = 3; break;
        case '6': *row = 2; break;
        case '7': *row = 1; break;
        case '8': *row = 0; break;
        default: return Err;
    }

    return Ok;
}

void movePiece(Slot board[][DIM], int originColumn, int originRow, int destinationColumn, int destinationRow, Color color) {
    // Deve existir estes índices dentro de board, senão comportamento indefinido

    Slot piece = board[originRow][originColumn];
    
    if (color == White) {
        board[originRow][originColumn] = WhiteTrail;
    } else {
        board[originRow][originColumn] = BlackTrail;
    }

    board[destinationRow][destinationColumn] = piece;
}

void clearPosition(Slot board[][DIM], int column, int row) {
    // Devem existir estes índices dentro de board, senão comportamento indefinido
    
    board[row][column] = Empty;
}

int main() {
    Slot board[][DIM] = {
        {Pt1, Pc1, Pb1, Pd1, Pr1, Pb2, Pc2, Pt2},
        {Pp1, Pp2, Pp3, Pp4, Pp5, Pp6, Pp7, Pp8},
        {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
        {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
        {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
        {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
        {Bp1, Bp2, Bp3, Bp4, Bp5, Bp6, Bp7, Bp8},
        {Bt1, Bc1, Bb1, Bd1, Br1, Bb2, Bc2, Bt2},
    };
    
    printf(NEUTRAL "\n              INÍCIO DA PARTIDA\n\n" RESET);
    printBoard(board);
    printf("\n");

    typedef struct {
        int rawOriginX;
        int rawOriginY;
        int rawDestinationX;
        int rawDestinationY;
        char* label;
    } Step;

    const Step steps[] = {
        {'e', '2', 'e', '4', "Brancas jogam e4"},
        {'e', '7', 'e', '5', "Pretas jogam e5"},
        {'f', '1', 'c', '4', "Brancas jogam Bc4"},
        {'b', '8', 'c', '6', "Pretas jogam Cc6"},
        {'d', '1', 'h', '5', "Brancas jogam Dh5"},
        {'g', '8', 'f', '6', "Pretas jogam Cf6"},
        {'h', '5', 'f', '7', "Brancas capturam Peão, xeque Mate: Dxf7#"},
    };

    for (int i = 0; i < sizeof(steps) / sizeof(Step); i++) {
        int originColumn, originRow, destinationColumn, destinationRow;

        if (deducePositionFromRaw(steps[i].rawOriginX, steps[i].rawOriginY, &originColumn, &originRow) == Err) {
            printf("Erro ao deduzir posição de origem.\n");
            return 1;
        }

        if (deducePositionFromRaw(steps[i].rawDestinationX, steps[i].rawDestinationY, &destinationColumn, &destinationRow) == Err) {
            printf("Erro ao deduzir posição de destino.\n");
            return 1;
        }

        printf(NEUTRAL);
        if (i % 2 == 0) {
            printf("\n                  JOGADA #%d\n\n", i / 2 + 1);
            movePiece(board, originColumn, originRow, destinationColumn, destinationRow, White);
        } else {
            movePiece(board, originColumn, originRow, destinationColumn, destinationRow, Black);
        }
        printf("   %s\n" RESET, steps[i].label);
        printBoard(board);
        printf("\n");

        clearPosition(board, originColumn, originRow);
    }

    return 0;
}

