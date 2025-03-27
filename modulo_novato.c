#include <stdio.h>
#include <SDL2/SDL.h>

#define TAMANHO_TABULEIRO 8
#define TAMANHO_QUADRADO 80

// Estrutura para posição
typedef struct {
    int x, y;
} Posicao;

// Verifica se a posição está dentro do tabuleiro
int dentroDoTabuleiro(int x, int y) {
    return x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO;
}

// Imprime posição (para debug)
void imprimirPosicao(int x, int y) {
    printf("(%d, %d)\n", x, y);
}

// Movimento da Torre
void moverTorre(Posicao pos, SDL_Renderer* renderer) {
    printf("Movimentos da Torre em (%d, %d):\n", pos.x, pos.y);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Vermelho para Torre
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (i != pos.x) {
            imprimirPosicao(i, pos.y);
            SDL_Rect rect = {i * TAMANHO_QUADRADO, pos.y * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
            SDL_RenderDrawRect(renderer, &rect);
        }
        if (i != pos.y) {
            imprimirPosicao(pos.x, i);
            SDL_Rect rect = {pos.x * TAMANHO_QUADRADO, i * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

// Movimento do Bispo
void moverBispo(Posicao pos, SDL_Renderer* renderer) {
    printf("Movimentos do Bispo em (%d, %d):\n", pos.x, pos.y);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde para Bispo
    int i, j;
    i = pos.x + 1; j = pos.y + 1;
    while (dentroDoTabuleiro(i, j)) {
        imprimirPosicao(i, j);
        SDL_Rect rect = {i * TAMANHO_QUADRADO, j * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
        SDL_RenderDrawRect(renderer, &rect);
        i++; j++;
    }
    i = pos.x - 1; j = pos.y + 1;
    while (dentroDoTabuleiro(i, j)) {
        imprimirPosicao(i, j);
        SDL_Rect rect = {i * TAMANHO_QUADRADO, j * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
        SDL_RenderDrawRect(renderer, &rect);
        i--; j++;
    }
    i = pos.x + 1; j = pos.y - 1;
    while (dentroDoTabuleiro(i, j)) {
        imprimirPosicao(i, j);
        SDL_Rect rect = {i * TAMANHO_QUADRADO, j * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
        SDL_RenderDrawRect(renderer, &rect);
        i++; j--;
    }
    i = pos.x - 1; j = pos.y - 1;
    while (dentroDoTabuleiro(i, j)) {
        imprimirPosicao(i, j);
        SDL_Rect rect = {i * TAMANHO_QUADRADO, j * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
        SDL_RenderDrawRect(renderer, &rect);
        i--; j--;
    }
}

// Movimento da Rainha
void moverRainha(Posicao pos, SDL_Renderer* renderer) {
    printf("Movimentos da Rainha em (%d, %d):\n", pos.x, pos.y);
    moverTorre(pos, renderer);
    moverBispo(pos, renderer);
}

// Desenha o tabuleiro
void desenharTabuleiro(SDL_Renderer* renderer) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Branco
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Preto
            }
            SDL_Rect rect = {i * TAMANHO_QUADRADO, j * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}



int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Xadrez - Modulo Novato", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          TAMANHO_TABULEIRO * TAMANHO_QUADRADO, TAMANHO_TABULEIRO * TAMANHO_QUADRADO, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Posicao pos = {3, 3};
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        desenharTabuleiro(renderer);
        moverTorre(pos, renderer);
        moverBispo(pos, renderer);
        moverRainha(pos, renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}