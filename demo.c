#include "chess_engine.h"

// Arquivo de demonstração para mostrar as funcionalidades do MateCheck
// Este arquivo pode ser usado para testar o projeto sem interface gráfica

void demoNovato() {
    printf("=== DEMONSTRAÇÃO MÓDULO NOVATO ===\n");
    printf("Conceitos: for, while, do-while\n\n");
    
    // Demonstração FOR
    printf("1. Demonstração FOR - Movimentos da Torre:\n");
    Position torre = {3, 3};
    printf("Torre na posição (%d, %d):\n", torre.x, torre.y);
    
    for (int x = 0; x < BOARD_SIZE; x++) {
        if (x != torre.x) {
            printf("  Torre pode mover para (%d, %d)\n", x, torre.y);
        }
    }
    
    // Demonstração WHILE
    printf("\n2. Demonstração WHILE - Movimentos verticais:\n");
    int y = 0;
    while (y < BOARD_SIZE) {
        if (y != torre.y) {
            printf("  Torre pode mover para (%d, %d)\n", torre.x, y);
        }
        y++;
    }
    
    // Demonstração DO-WHILE
    printf("\n3. Demonstração DO-WHILE:\n");
    int count = 0;
    do {
        printf("  Iteração %d do DO-WHILE\n", count + 1);
        count++;
    } while (count < 3);
}

void demoAventureiro() {
    printf("\n=== DEMONSTRAÇÃO MÓDULO AVENTUREIRO ===\n");
    printf("Conceitos: loops aninhados, validação de limites\n\n");
    
    // Demonstração de loops aninhados
    printf("1. Demonstração de loops aninhados - Movimentos do Cavalo:\n");
    Position cavalo = {3, 3};
    printf("Cavalo na posição (%d, %d):\n", cavalo.x, cavalo.y);
    
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    for (int i = 0; i < 8; i++) {
        int newX = cavalo.x + knightMoves[i][0];
        int newY = cavalo.y + knightMoves[i][1];
        
        if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
            printf("  Cavalo pode mover para (%d, %d)\n", newX, newY);
        } else {
            printf("  Movimento para (%d, %d) está fora do tabuleiro\n", newX, newY);
        }
    }
    
    // Demonstração de busca em matriz
    printf("\n2. Demonstração de busca em matriz 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("  Posição [%d][%d] = %d\n", i, j, i * 3 + j);
        }
    }
}

void demoMestre() {
    printf("\n=== DEMONSTRAÇÃO MÓDULO MESTRE ===\n");
    printf("Conceitos: recursividade, backtracking, otimização\n\n");
    
    // Demonstração de recursividade
    printf("1. Demonstração de recursividade - Fatorial:\n");
    int n = 5;
    printf("Fatorial de %d = %d\n", n, fatorial(n));
    
    // Demonstração de Fibonacci
    printf("\n2. Demonstração de Fibonacci:\n");
    for (int i = 0; i < 10; i++) {
        printf("  Fibonacci(%d) = %d\n", i, fibonacci(i));
    }
    
    // Demonstração de busca recursiva
    printf("\n3. Demonstração de busca recursiva do cavalo:\n");
    Position start = {0, 0};
    Position end = {2, 2};
    printf("Buscando caminho de (%d, %d) para (%d, %d):\n", start.x, start.y, end.x, end.y);
    
    bool visited[BOARD_SIZE][BOARD_SIZE] = {false};
    int minMoves = findKnightMinMoves(start, end, visited, 0);
    printf("Menor número de movimentos: %d\n", minMoves);
}

int fatorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
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

int main() {
    printf("========================================\n");
    printf("    MATE CHECK - DEMONSTRAÇÃO\n");
    printf("    Desenvolvido por Daniel Barbieri Dev\n");
    printf("========================================\n\n");
    
    // Executar demonstrações
    demoNovato();
    demoAventureiro();
    demoMestre();
    
    printf("\n========================================\n");
    printf("    DEMONSTRAÇÃO CONCLUÍDA!\n");
    printf("    Para executar o jogo completo:\n");
    printf("    make run\n");
    printf("========================================\n");
    
    return 0;
}
