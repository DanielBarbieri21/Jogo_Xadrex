#include "../chess_engine.h"

// Módulo Aventureiro - Cavalo
// Demonstra loops aninhados para movimento em "L"

void runAventureiroModule(ChessGame* game) {
    printf("=== MÓDULO AVENTUREIRO ===\n");
    printf("Aprenda o movimento em 'L' do Cavalo usando loops aninhados\n");
    printf("Conceitos: loops aninhados, validação de limites\n\n");
    
    // Configurar tabuleiro para demonstração
    initAventureiroBoard(&game->board);
    
    // Demonstração do Cavalo
    printf("--- MOVIMENTOS DO CAVALO ---\n");
    demonstrateKnightMoves(game);
    
    // Demonstração de loops aninhados
    printf("\n--- LOOPS ANINHADOS ---\n");
    demonstrateNestedLoops(game);
}

void initAventureiroBoard(ChessBoard* board) {
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
    
    // Colocar cavalo na posição central
    board->board[3][3].type = PIECE_KNIGHT;
    board->board[3][3].color = COLOR_WHITE_PIECE;
}

void demonstrateKnightMoves(ChessGame* game) {
    Position knightPos = {3, 3};
    printf("Cavalo na posição (%d, %d):\n", knightPos.x, knightPos.y);
    
    // Usando loops aninhados para encontrar movimentos em "L"
    printf("Movimentos possíveis (usando loops aninhados):\n");
    
    // Array de deslocamentos para movimento em "L"
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    // Loop principal para verificar cada movimento possível
    for (int i = 0; i < 8; i++) {
        int newX = knightPos.x + knightMoves[i][0];
        int newY = knightPos.y + knightMoves[i][1];
        
        // Validação de limites usando função auxiliar
        if (isPositionValid((Position){newX, newY})) {
            printf("  Cavalo pode mover para (%d, %d)\n", newX, newY);
        } else {
            printf("  Movimento para (%d, %d) está fora do tabuleiro\n", newX, newY);
        }
    }
}

void demonstrateNestedLoops(ChessGame* game) {
    printf("Demonstração de loops aninhados:\n");
    printf("Simulando busca em uma matriz 3x3:\n");
    
    // Loop aninhado para percorrer uma matriz
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("  Posição [%d][%d] = %d\n", i, j, i * 3 + j);
        }
    }
    
    printf("\nSimulando movimento do cavalo em todas as posições:\n");
    
    // Loop aninhado para testar cavalo em diferentes posições
    for (int startX = 0; startX < 3; startX++) {
        for (int startY = 0; startY < 3; startY++) {
            printf("Cavalo em (%d, %d): ", startX, startY);
            
            // Contar movimentos válidos
            int validMoves = 0;
            int knightMoves[8][2] = {
                {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
            };
            
            for (int k = 0; k < 8; k++) {
                int newX = startX + knightMoves[k][0];
                int newY = startY + knightMoves[k][1];
                
                if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                    validMoves++;
                }
            }
            
            printf("%d movimentos válidos\n", validMoves);
        }
    }
}

void demonstrateKnightPathfinding(ChessGame* game) {
    printf("\n--- ALGORITMO DE BUSCA DO CAVALO ---\n");
    printf("Encontrando caminho do cavalo entre duas posições:\n");
    
    Position start = {0, 0};
    Position end = {2, 2};
    
    printf("Início: (%d, %d)\n", start.x, start.y);
    printf("Fim: (%d, %d)\n", end.x, end.y);
    
    // Algoritmo simples de busca em largura (BFS) para cavalo
    findKnightPath(start, end);
}

void findKnightPath(Position start, Position end) {
    // Implementação simplificada de busca de caminho
    printf("Buscando caminho...\n");
    
    // Para demonstração, vamos usar uma abordagem simples
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    Position current = start;
    int steps = 0;
    int maxSteps = 10; // Limite para evitar loop infinito
    
    printf("Caminho encontrado: ");
    printf("(%d, %d) ", current.x, current.y);
    
    while ((current.x != end.x || current.y != end.y) && steps < maxSteps) {
        // Encontrar o movimento que mais se aproxima do destino
        int bestMove = -1;
        int bestDistance = 999;
        
        for (int i = 0; i < 8; i++) {
            int newX = current.x + knightMoves[i][0];
            int newY = current.y + knightMoves[i][1];
            
            if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
                int distance = abs(newX - end.x) + abs(newY - end.y);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestMove = i;
                }
            }
        }
        
        if (bestMove != -1) {
            current.x += knightMoves[bestMove][0];
            current.y += knightMoves[bestMove][1];
            steps++;
            printf("-> (%d, %d) ", current.x, current.y);
        } else {
            break;
        }
    }
    
    printf("\nTotal de passos: %d\n", steps);
}

void drawAventureiroUI(ChessGame* game) {
    // Desenhar informações específicas do módulo Aventureiro
    drawText(game, "MÓDULO AVENTUREIRO", 920, 50, COLOR_HIGHLIGHT);
    drawText(game, "Cavalo: Movimento", 920, 80, COLOR_WHITE);
    drawText(game, "em 'L'", 920, 100, COLOR_WHITE);
    
    drawText(game, "Conceitos:", 920, 150, COLOR_LIGHT_BROWN);
    drawText(game, "- Loops aninhados", 920, 170, COLOR_WHITE);
    drawText(game, "- Validação de", 920, 190, COLOR_WHITE);
    drawText(game, "  limites", 920, 210, COLOR_WHITE);
    drawText(game, "- Arrays 2D", 920, 230, COLOR_WHITE);
    
    // Mostrar movimentos do cavalo
    drawText(game, "Movimentos L:", 920, 300, COLOR_LIGHT_BROWN);
    drawText(game, "±2,±1 e ±1,±2", 920, 320, COLOR_WHITE);
    
    // Estatísticas
    char statsText[50];
    sprintf(statsText, "Máx. movimentos: 8");
    drawText(game, statsText, 920, 400, COLOR_WHITE);
}
