#include "chess_engine.h"

int main(int argc, char* argv[]) {
    ChessGame game = {0};
    
    if (!initGame(&game)) {
        printf("Erro ao inicializar o jogo!\n");
        return 1;
    }
    
    runGame(&game);
    cleanupGame(&game);
    
    return 0;
}
