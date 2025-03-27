#include <stdio.h>
#include <SDL2/SDL.h>

#define TAMANHO_TABULEIRO 8
#define TAMANHO_QUADRADO 80

typedef struct {
    int x, y;
} Posicao;

int dentroDoTabuleiro(int x, int y) {
    return x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO;
}

void moverCavalo(Posicao pos, SDL_Renderer* renderer) {
    printf("Movimentos do Cavalo em (%d, %d):\n", pos.x, pos.y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Azul para Cavalo
    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
    for (int i = 0; i < 8; i++) {
        int novoX = pos.x + dx[i];
        int novoY = pos.y + dy[i];
        if (dentroDoTabuleiro(novoX, novoY)) {
            printf("(%d, %d)\n", novoX, novoY);
            SDL_Rect rect = {novoX * TAMANHO_QUADRADO, novoY * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void desenharTabuleiro(SDL_Renderer* renderer) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_Rect rect = {i * TAMANHO_QUADRADO, j * TAMANHO_QUADRADO, TAMANHO_QUADRADO, TAMANHO_QUADRADO};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Xadrez - Modulo Aventureiro", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
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
        moverCavalo(pos, renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}