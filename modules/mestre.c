#include "../chess_engine.h"

// Módulo Mestre - Algoritmo Recursivo
// Demonstra recursividade para encontrar o menor caminho do cavalo

void runMestreModule(ChessGame* game) {
    printf("=== MÓDULO MESTRE ===\n");
    printf("Algoritmo recursivo para encontrar o menor caminho do cavalo\n");
    printf("Conceitos: recursividade, backtracking, otimização\n\n");
    
    // Configurar tabuleiro para demonstração
    initMestreBoard(&game->board);
    
    // Demonstração do algoritmo recursivo
    printf("--- ALGORITMO RECURSIVO DO CAVALO ---\n");
    demonstrateRecursiveKnight(game);
    
    // Demonstração de otimização
    printf("\n--- OTIMIZAÇÃO COM MEMOIZAÇÃO ---\n");
    demonstrateOptimizedKnight(game);
}

void initMestreBoard(ChessBoard* board) {
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
    
    // Colocar cavalo na posição inicial
    board->board[0][0].type = PIECE_KNIGHT;
    board->board[0][0].color = COLOR_WHITE_PIECE;
}

void demonstrateRecursiveKnight(ChessGame* game) {
    Position start = {0, 0};
    Position end = {7, 7};
    
    printf("Encontrando menor caminho do cavalo de (%d, %d) para (%d, %d):\n", 
           start.x, start.y, end.x, end.y);
    
    // Matriz para rastrear posições visitadas
    bool visited[BOARD_SIZE][BOARD_SIZE] = {false};
    
    // Encontrar caminho usando recursividade
    int minMoves = findKnightMinMoves(start, end, visited, 0);
    
    printf("Menor número de movimentos: %d\n", minMoves);
    
    // Demonstrar diferentes algoritmos
    printf("\nComparando algoritmos:\n");
    compareAlgorithms(start, end);
}

int findKnightMinMoves(Position current, Position target, bool visited[][BOARD_SIZE], int depth) {
    // Caso base: chegou ao destino
    if (current.x == target.x && current.y == target.y) {
        return depth;
    }
    
    // Caso base: posição inválida ou já visitada
    if (!isPositionValid(current) || visited[current.x][current.y]) {
        return INT_MAX;
    }
    
    // Marcar posição como visitada
    visited[current.x][current.y] = true;
    
    int minMoves = INT_MAX;
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    // Tentar todos os movimentos possíveis
    for (int i = 0; i < 8; i++) {
        Position next = {
            current.x + knightMoves[i][0],
            current.y + knightMoves[i][1]
        };
        
        if (isPositionValid(next)) {
            int moves = findKnightMinMoves(next, target, visited, depth + 1);
            if (moves < minMoves) {
                minMoves = moves;
            }
        }
    }
    
    // Desmarcar posição (backtracking)
    visited[current.x][current.y] = false;
    
    return minMoves;
}

void demonstrateOptimizedKnight(ChessGame* game) {
    printf("Implementação otimizada com memoização:\n");
    
    Position start = {0, 0};
    Position end = {7, 7};
    
    // Matriz de memoização
    int memo[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            memo[i][j] = -1; // -1 significa não calculado
        }
    }
    
    int optimizedMoves = findKnightMinMovesOptimized(start, end, memo);
    printf("Menor número de movimentos (otimizado): %d\n", optimizedMoves);
    
    // Demonstrar diferença de performance
    printf("\nComparação de performance:\n");
    comparePerformance(start, end);
}

int findKnightMinMovesOptimized(Position current, Position target, int memo[][BOARD_SIZE]) {
    // Caso base: chegou ao destino
    if (current.x == target.x && current.y == target.y) {
        return 0;
    }
    
    // Caso base: posição inválida
    if (!isPositionValid(current)) {
        return INT_MAX;
    }
    
    // Verificar se já foi calculado (memoização)
    if (memo[current.x][current.y] != -1) {
        return memo[current.x][current.y];
    }
    
    int minMoves = INT_MAX;
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    // Tentar todos os movimentos possíveis
    for (int i = 0; i < 8; i++) {
        Position next = {
            current.x + knightMoves[i][0],
            current.y + knightMoves[i][1]
        };
        
        if (isPositionValid(next)) {
            int moves = findKnightMinMovesOptimized(next, target, memo);
            if (moves != INT_MAX && moves + 1 < minMoves) {
                minMoves = moves + 1;
            }
        }
    }
    
    // Salvar resultado na memoização
    memo[current.x][current.y] = minMoves;
    return minMoves;
}

void compareAlgorithms(Position start, Position end) {
    printf("1. Algoritmo recursivo simples:\n");
    printf("   - Complexidade: O(8^n) onde n é a profundidade\n");
    printf("   - Vantagem: Código simples e fácil de entender\n");
    printf("   - Desvantagem: Muito lento para distâncias grandes\n");
    
    printf("\n2. Algoritmo com memoização:\n");
    printf("   - Complexidade: O(n²) onde n é o tamanho do tabuleiro\n");
    printf("   - Vantagem: Muito mais rápido\n");
    printf("   - Desvantagem: Usa mais memória\n");
    
    printf("\n3. Algoritmo BFS (Breadth-First Search):\n");
    printf("   - Complexidade: O(n²)\n");
    printf("   - Vantagem: Garante o caminho mais curto\n");
    printf("   - Desvantagem: Mais complexo de implementar\n");
}

void comparePerformance(Position start, Position end) {
    printf("Testando performance com diferentes distâncias:\n");
    
    Position testCases[4] = {
        {0, 0}, {3, 3}, {6, 6}, {7, 7}
    };
    
    for (int i = 0; i < 4; i++) {
        printf("De (%d, %d) para (%d, %d): ", 
               start.x, start.y, testCases[i].x, testCases[i].y);
        
        // Simular cálculo (em um caso real, mediríamos o tempo)
        int distance = abs(testCases[i].x - start.x) + abs(testCases[i].y - start.y);
        int estimatedMoves = (distance + 2) / 3; // Estimativa simples
        
        printf("%d movimentos estimados\n", estimatedMoves);
    }
}

void demonstrateBacktracking(ChessGame* game) {
    printf("\n--- DEMONSTRAÇÃO DE BACKTRACKING ---\n");
    printf("O backtracking é essencial para:\n");
    printf("1. Evitar loops infinitos\n");
    printf("2. Encontrar todas as soluções possíveis\n");
    printf("3. Otimizar o espaço de busca\n");
    
    printf("\nExemplo de backtracking no cavalo:\n");
    printf("1. Marcar posição como visitada\n");
    printf("2. Tentar todos os movimentos possíveis\n");
    printf("3. Se não encontrar solução, desmarcar posição\n");
    printf("4. Tentar próximo movimento\n");
}

void drawMestreUI(ChessGame* game) {
    // Desenhar informações específicas do módulo Mestre
    drawText(game, "MÓDULO MESTRE", 920, 50, COLOR_HIGHLIGHT);
    drawText(game, "Algoritmo", 920, 80, COLOR_WHITE);
    drawText(game, "Recursivo", 920, 100, COLOR_WHITE);
    
    drawText(game, "Conceitos:", 920, 150, COLOR_LIGHT_BROWN);
    drawText(game, "- Recursividade", 920, 170, COLOR_WHITE);
    drawText(game, "- Backtracking", 920, 190, COLOR_WHITE);
    drawText(game, "- Memoização", 920, 210, COLOR_WHITE);
    drawText(game, "- Otimização", 920, 230, COLOR_WHITE);
    
    // Mostrar complexidade
    drawText(game, "Complexidade:", 920, 300, COLOR_LIGHT_BROWN);
    drawText(game, "Simples: O(8^n)", 920, 320, COLOR_WHITE);
    drawText(game, "Otimizado: O(n²)", 920, 340, COLOR_WHITE);
    
    // Estatísticas avançadas
    char statsText[50];
    sprintf(statsText, "Posições testadas: %d", game->board.moveCount);
    drawText(game, statsText, 920, 400, COLOR_WHITE);
}
