#include "../chess_engine.h"

// Módulo Novato - Torre, Bispo e Rainha
// Demonstra estruturas de repetição simples (for, while, do-while)

void runNovatoModule(ChessGame* game) {
    printf("=== MÓDULO NOVATO ===\n");
    printf("Aprenda os movimentos básicos da Torre, Bispo e Rainha\n");
    printf("Usando estruturas de repetição: for, while, do-while\n\n");
    
    // Configurar tabuleiro para demonstração
    initNovatoBoard(&game->board);
    
    // Demonstração da Torre
    printf("--- MOVIMENTOS DA TORRE ---\n");
    demonstrateRookMoves(game);
    
    // Demonstração do Bispo
    printf("\n--- MOVIMENTOS DO BISPO ---\n");
    demonstrateBishopMoves(game);
    
    // Demonstração da Rainha
    printf("\n--- MOVIMENTOS DA RAINHA ---\n");
    demonstrateQueenMoves(game);
}

void initNovatoBoard(ChessBoard* board) {
    // Limpar tabuleiro
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->board[i][j].type = PIECE_NONE;
            board->board[i][j].color = COLOR_WHITE_PIECE;
            board->board[i][j].pos.x = i;
            board->board[i][j].pos.y = j;
            board->board[i][j].hasMoved = false;
        }
    }
    
    // Colocar peças de demonstração
    // Torre na posição (3, 3)
    board->board[3][3].type = PIECE_ROOK;
    board->board[3][3].color = COLOR_WHITE_PIECE;
    
    // Bispo na posição (4, 4)
    board->board[4][4].type = PIECE_BISHOP;
    board->board[4][4].color = COLOR_WHITE_PIECE;
    
    // Rainha na posição (2, 2)
    board->board[2][2].type = PIECE_QUEEN;
    board->board[2][2].color = COLOR_WHITE_PIECE;
}

void demonstrateRookMoves(ChessGame* game) {
    Position rookPos = {3, 3};
    printf("Torre na posição (%d, %d):\n", rookPos.x, rookPos.y);
    
    // Usando FOR para movimentos horizontais
    printf("Movimentos horizontais (usando FOR):\n");
    for (int x = 0; x < BOARD_SIZE; x++) {
        if (x != rookPos.x) {
            printf("  Torre pode mover para (%d, %d)\n", x, rookPos.y);
        }
    }
    
    // Usando WHILE para movimentos verticais
    printf("Movimentos verticais (usando WHILE):\n");
    int y = 0;
    while (y < BOARD_SIZE) {
        if (y != rookPos.y) {
            printf("  Torre pode mover para (%d, %d)\n", rookPos.x, y);
        }
        y++;
    }
    
    // Usando DO-WHILE para demonstrar conceito
    printf("Demonstração DO-WHILE:\n");
    int count = 0;
    do {
        printf("  Iteração %d do DO-WHILE\n", count + 1);
        count++;
    } while (count < 3);
}

void demonstrateBishopMoves(ChessGame* game) {
    Position bishopPos = {4, 4};
    printf("Bispo na posição (%d, %d):\n", bishopPos.x, bishopPos.y);
    
    // Usando FOR para diagonal principal
    printf("Diagonal principal (usando FOR):\n");
    for (int i = 1; i < BOARD_SIZE; i++) {
        int newX = bishopPos.x + i;
        int newY = bishopPos.y + i;
        if (newX < BOARD_SIZE && newY < BOARD_SIZE) {
            printf("  Bispo pode mover para (%d, %d)\n", newX, newY);
        }
    }
    
    // Usando WHILE para diagonal secundária
    printf("Diagonal secundária (usando WHILE):\n");
    int i = 1;
    while (bishopPos.x + i < BOARD_SIZE && bishopPos.y - i >= 0) {
        printf("  Bispo pode mover para (%d, %d)\n", bishopPos.x + i, bishopPos.y - i);
        i++;
    }
}

void demonstrateQueenMoves(ChessGame* game) {
    Position queenPos = {2, 2};
    printf("Rainha na posição (%d, %d):\n", queenPos.x, queenPos.y);
    printf("A Rainha combina movimentos da Torre e do Bispo!\n");
    
    // A rainha usa as mesmas funções da torre e bispo
    printf("Movimentos da Rainha (combinação de Torre + Bispo):\n");
    
    // Movimentos horizontais e verticais (como a Torre)
    printf("Movimentos lineares:\n");
    for (int x = 0; x < BOARD_SIZE; x++) {
        if (x != queenPos.x) {
            printf("  Rainha pode mover para (%d, %d)\n", x, queenPos.y);
        }
    }
    
    for (int y = 0; y < BOARD_SIZE; y++) {
        if (y != queenPos.y) {
            printf("  Rainha pode mover para (%d, %d)\n", queenPos.x, y);
        }
    }
    
    // Movimentos diagonais (como o Bispo)
    printf("Movimentos diagonais:\n");
    for (int i = 1; i < BOARD_SIZE; i++) {
        int newX = queenPos.x + i;
        int newY = queenPos.y + i;
        if (newX < BOARD_SIZE && newY < BOARD_SIZE) {
            printf("  Rainha pode mover para (%d, %d)\n", newX, newY);
        }
    }
}

void drawNovatoUI(ChessGame* game) {
    // Desenhar informações específicas do módulo Novato
    drawText(game, "MÓDULO NOVATO", 920, 50, COLOR_HIGHLIGHT);
    drawText(game, "Torre: Movimentos", 920, 80, COLOR_WHITE);
    drawText(game, "horizontais e", 920, 100, COLOR_WHITE);
    drawText(game, "verticais", 920, 120, COLOR_WHITE);
    
    drawText(game, "Bispo: Movimentos", 920, 200, COLOR_WHITE);
    drawText(game, "diagonais", 920, 220, COLOR_WHITE);
    
    drawText(game, "Rainha: Combina", 920, 300, COLOR_WHITE);
    drawText(game, "Torre + Bispo", 920, 320, COLOR_WHITE);
    
    // Mostrar conceitos de programação
    drawText(game, "Conceitos:", 920, 400, COLOR_LIGHT_BROWN);
    drawText(game, "- FOR loops", 920, 420, COLOR_WHITE);
    drawText(game, "- WHILE loops", 920, 440, COLOR_WHITE);
    drawText(game, "- DO-WHILE loops", 920, 460, COLOR_WHITE);
}
