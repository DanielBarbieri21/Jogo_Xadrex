#include "chess_engine.h"

void drawMenu(ChessGame* game, Menu* menu) {
    // Desenhar fundo
    SDL_SetRenderDrawColor(game->renderer, 20, 20, 40, 255);
    SDL_RenderClear(game->renderer);
    
    // Título
    drawText(game, "MATE CHECK", WINDOW_WIDTH/2 - 100, 100, COLOR_WHITE);
    drawText(game, "Jogo de Xadrez Educacional", WINDOW_WIDTH/2 - 150, 140, COLOR_LIGHT_BROWN);
    
    // Opções do menu
    for (int i = 0; i < menu->totalOptions; i++) {
        SDL_Color color = (i == menu->selectedOption) ? COLOR_HIGHLIGHT : COLOR_WHITE;
        int y = 250 + i * 50;
        
        // Destacar opção selecionada
        if (i == menu->selectedOption) {
            SDL_Rect highlightRect = {WINDOW_WIDTH/2 - 200, y - 5, 400, 40};
            SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 50);
            SDL_RenderFillRect(game->renderer, &highlightRect);
        }
        
        drawText(game, menu->options[i], WINDOW_WIDTH/2 - 180, y, color);
    }
    
    // Instruções
    drawText(game, "Use as setas para navegar e ENTER para selecionar", 
             WINDOW_WIDTH/2 - 200, WINDOW_HEIGHT - 100, COLOR_LIGHT_BROWN);
    drawText(game, "ESC para sair", WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT - 70, COLOR_LIGHT_BROWN);
}

void handleMenuInput(ChessGame* game, Menu* menu, SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                menu->selectedOption = (menu->selectedOption - 1 + menu->totalOptions) % menu->totalOptions;
                playSound(game, game->moveSound);
                break;
            case SDLK_DOWN:
                menu->selectedOption = (menu->selectedOption + 1) % menu->totalOptions;
                playSound(game, game->moveSound);
                break;
            case SDLK_RETURN:
            case SDLK_SPACE:
                switch (menu->selectedOption) {
                    case 0: // Novato
                        game->difficulty = 1;
                        menu->isActive = false;
                        playSound(game, game->captureSound);
                        break;
                    case 1: // Aventureiro
                        game->difficulty = 2;
                        menu->isActive = false;
                        playSound(game, game->captureSound);
                        break;
                    case 2: // Mestre
                        game->difficulty = 3;
                        menu->isActive = false;
                        playSound(game, game->captureSound);
                        break;
                    case 3: // Sair
                        game->running = false;
                        break;
                }
                break;
            case SDLK_ESCAPE:
                game->running = false;
                break;
        }
    }
}

void drawUI(ChessGame* game) {
    // Painel lateral
    SDL_Rect panelRect = {900, 0, 100, WINDOW_HEIGHT};
    SDL_SetRenderDrawColor(game->renderer, 40, 40, 60, 255);
    SDL_RenderFillRect(game->renderer, &panelRect);
    
    // Informações do jogo
    char scoreText[50];
    sprintf(scoreText, "Pontos: %d", game->score);
    drawText(game, scoreText, 920, 150, COLOR_WHITE);
    
    char moveText[50];
    sprintf(moveText, "Movimentos: %d", game->board.moveCount);
    drawText(game, moveText, 920, 180, COLOR_WHITE);
    
    char playerText[50];
    sprintf(playerText, "Jogador: %s", game->playerName);
    drawText(game, playerText, 920, 210, COLOR_WHITE);
    
    // Instruções
    drawText(game, "Clique para", 920, 300, COLOR_LIGHT_BROWN);
    drawText(game, "selecionar", 920, 320, COLOR_LIGHT_BROWN);
    drawText(game, "Clique para", 920, 350, COLOR_LIGHT_BROWN);
    drawText(game, "mover", 920, 370, COLOR_LIGHT_BROWN);
    drawText(game, "ESC para", 920, 400, COLOR_LIGHT_BROWN);
    drawText(game, "desselecionar", 920, 420, COLOR_LIGHT_BROWN);
    drawText(game, "R para", 920, 450, COLOR_LIGHT_BROWN);
    drawText(game, "reiniciar", 920, 470, COLOR_LIGHT_BROWN);
    
    // Dificuldade atual
    char diffText[30];
    switch (game->difficulty) {
        case 1: strcpy(diffText, "Novato"); break;
        case 2: strcpy(diffText, "Aventureiro"); break;
        case 3: strcpy(diffText, "Mestre"); break;
        default: strcpy(diffText, "Desconhecido"); break;
    }
    drawText(game, diffText, 920, 550, COLOR_HIGHLIGHT);
}

void drawText(ChessGame* game, const char* text, int x, int y, SDL_Color color) {
    if (!game->font) return;
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(game->font, text, color);
    if (!textSurface) return;
    
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        return;
    }
    
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);
    
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

bool initAudio(ChessGame* game) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erro ao inicializar áudio: %s\n", Mix_GetError());
        return false;
    }
    
    // Carregar sons (se existirem)
    game->backgroundMusic = Mix_LoadMUS("assets/sounds/background.wav");
    game->moveSound = Mix_LoadWAV("assets/sounds/move.wav");
    game->captureSound = Mix_LoadWAV("assets/sounds/capture.wav");
    
    // Se não conseguir carregar os arquivos, criar sons simples
    if (!game->moveSound) {
        // Criar som simples de movimento
        game->moveSound = createSimpleSound(440, 0.1); // Nota Lá
    }
    if (!game->captureSound) {
        // Criar som simples de captura
        game->captureSound = createSimpleSound(880, 0.2); // Nota Lá oitava
    }
    
    return true;
}

Mix_Chunk* createSimpleSound(int frequency, float duration) {
    // Esta é uma implementação simplificada
    // Em um projeto real, você usaria bibliotecas como PortAudio
    return NULL;
}

void playSound(ChessGame* game, Mix_Chunk* sound) {
    if (sound) {
        Mix_PlayChannel(-1, sound, 0);
    }
}

SDL_Color hexToColor(int hex) {
    SDL_Color color;
    color.r = (hex >> 16) & 0xFF;
    color.g = (hex >> 8) & 0xFF;
    color.b = hex & 0xFF;
    color.a = 255;
    return color;
}
