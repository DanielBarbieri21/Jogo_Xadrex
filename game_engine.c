#include "chess_engine.h"

bool initGame(ChessGame* game) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return false;
    }
    
    // Inicializar TTF
    if (TTF_Init() < 0) {
        printf("Erro ao inicializar TTF: %s\n", TTF_GetError());
        return false;
    }
    
    // Criar janela
    game->window = SDL_CreateWindow(
        "MateCheck - Jogo de Xadrez Educacional",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    
    if (!game->window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        return false;
    }
    
    // Criar renderer
    game->renderer = SDL_CreateRenderer(
        game->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (!game->renderer) {
        printf("Erro ao criar renderer: %s\n", SDL_GetError());
        return false;
    }
    
    // Carregar fontes
    game->font = TTF_OpenFont("assets/fonts/arial.ttf", 16);
    game->bigFont = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    
    if (!game->font || !game->bigFont) {
        printf("Erro ao carregar fontes. Usando fonte padrão.\n");
        // Usar fonte padrão do sistema
        game->font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
        game->bigFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    }
    
    // Inicializar áudio
    initAudio(game);
    
    // Inicializar tabuleiro
    initBoard(&game->board);
    
    // Configurações padrão
    game->running = true;
    game->showMoves = false;
    game->difficulty = 1;
    game->score = 0;
    strcpy(game->playerName, "Jogador");
    
    return true;
}

void cleanupGame(ChessGame* game) {
    if (game->backgroundMusic) {
        Mix_FreeMusic(game->backgroundMusic);
    }
    if (game->moveSound) {
        Mix_FreeChunk(game->moveSound);
    }
    if (game->captureSound) {
        Mix_FreeChunk(game->captureSound);
    }
    
    if (game->font) {
        TTF_CloseFont(game->font);
    }
    if (game->bigFont) {
        TTF_CloseFont(game->bigFont);
    }
    
    if (game->renderer) {
        SDL_DestroyRenderer(game->renderer);
    }
    if (game->window) {
        SDL_DestroyWindow(game->window);
    }
    
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void runGame(ChessGame* game) {
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    float deltaTime;
    
    Menu mainMenu = {
        .selectedOption = 0,
        .totalOptions = 4,
        .isActive = true
    };
    strcpy(mainMenu.options[0], "Novato - Torre, Bispo, Rainha");
    strcpy(mainMenu.options[1], "Aventureiro - Cavalo");
    strcpy(mainMenu.options[2], "Mestre - Algoritmo Recursivo");
    strcpy(mainMenu.options[3], "Sair");
    
    while (game->running) {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        // Processar eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game->running = false;
            }
            
            if (mainMenu.isActive) {
                handleMenuInput(game, &mainMenu, &event);
            } else {
                // Lógica de jogo baseada no módulo selecionado
                handleGameInput(game, &event);
            }
        }
        
        // Renderizar
        SDL_SetRenderDrawColor(game->renderer, 30, 30, 30, 255);
        SDL_RenderClear(game->renderer);
        
        if (mainMenu.isActive) {
            drawMenu(game, &mainMenu);
        } else {
            drawBoard(game);
            drawUI(game);
        }
        
        SDL_RenderPresent(game->renderer);
        
        // Controle de FPS
        if (deltaTime < 1.0f / FPS) {
            SDL_Delay((Uint32)((1.0f / FPS - deltaTime) * 1000));
        }
    }
}

void handleGameInput(ChessGame* game, SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            int mouseX = event->button.x;
            int mouseY = event->button.y;
            
            // Converter coordenadas do mouse para posição no tabuleiro
            int boardX = (mouseX - 100) / SQUARE_SIZE;
            int boardY = (mouseY - 100) / SQUARE_SIZE;
            
            if (boardX >= 0 && boardX < BOARD_SIZE && boardY >= 0 && boardY < BOARD_SIZE) {
                Position clickedPos = {boardX, boardY};
                
                if (!game->board.isSelected) {
                    // Selecionar peça
                    Piece* piece = getPieceAt(&game->board, clickedPos);
                    if (piece && piece->type != PIECE_NONE) {
                        game->board.selected = clickedPos;
                        game->board.isSelected = true;
                        game->showMoves = true;
                        playSound(game, game->moveSound);
                    }
                } else {
                    // Mover peça ou desselecionar
                    if (isValidMove(&game->board, game->board.selected, clickedPos)) {
                        makeMove(&game->board, game->board.selected, clickedPos);
                        game->score += 10;
                        playSound(game, game->captureSound);
                    }
                    game->board.isSelected = false;
                    game->showMoves = false;
                }
            }
        }
    }
    
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                game->board.isSelected = false;
                game->showMoves = false;
                break;
            case SDLK_r:
                initBoard(&game->board);
                game->score = 0;
                break;
        }
    }
}
