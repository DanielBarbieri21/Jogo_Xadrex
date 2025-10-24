#ifndef CHESS_ENGINE_H
#define CHESS_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Constantes do jogo
#define BOARD_SIZE 8
#define SQUARE_SIZE 100
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define FPS 60

// Cores modernas
#define COLOR_WHITE {255, 255, 255, 255}
#define COLOR_BLACK {0, 0, 0, 255}
#define COLOR_LIGHT_BROWN {240, 217, 181, 255}
#define COLOR_DARK_BROWN {181, 136, 99, 255}
#define COLOR_HIGHLIGHT {255, 255, 0, 255}
#define COLOR_MOVE_HINT {0, 255, 0, 255}
#define COLOR_ATTACK {255, 0, 0, 255}
#define COLOR_SELECTED {0, 0, 255, 255}

// Tipos de peças
typedef enum {
    PIECE_NONE = 0,
    PIECE_PAWN,
    PIECE_ROOK,
    PIECE_KNIGHT,
    PIECE_BISHOP,
    PIECE_QUEEN,
    PIECE_KING
} PieceType;

// Cores das peças
typedef enum {
    COLOR_WHITE_PIECE = 0,
    COLOR_BLACK_PIECE = 1
} PieceColor;

// Estrutura de posição
typedef struct {
    int x, y;
} Position;

// Estrutura de peça
typedef struct {
    PieceType type;
    PieceColor color;
    Position pos;
    bool hasMoved;
} Piece;

// Estrutura do tabuleiro
typedef struct {
    Piece board[BOARD_SIZE][BOARD_SIZE];
    Position selected;
    bool isSelected;
    int currentPlayer;
    int moveCount;
} ChessBoard;

// Estrutura do jogo
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    TTF_Font* bigFont;
    Mix_Music* backgroundMusic;
    Mix_Chunk* moveSound;
    Mix_Chunk* captureSound;
    ChessBoard board;
    bool running;
    bool showMoves;
    int difficulty;
    int score;
    char playerName[50];
} ChessGame;

// Estrutura de menu
typedef struct {
    int selectedOption;
    int totalOptions;
    char options[10][50];
    bool isActive;
} Menu;

// Funções principais
bool initGame(ChessGame* game);
void cleanupGame(ChessGame* game);
void runGame(ChessGame* game);

// Funções do tabuleiro
void initBoard(ChessBoard* board);
void drawBoard(ChessGame* game);
void drawPiece(ChessGame* game, Piece piece, int x, int y);
void drawSquare(ChessGame* game, int x, int y, SDL_Color color);

// Funções de movimento
bool isValidMove(ChessBoard* board, Position from, Position to);
void makeMove(ChessBoard* board, Position from, Position to);
void getPossibleMoves(ChessBoard* board, Position pos, Position moves[], int* count);

// Funções de peças específicas
void getPawnMoves(ChessBoard* board, Position pos, Position moves[], int* count);
void getRookMoves(ChessBoard* board, Position pos, Position moves[], int* count);
void getBishopMoves(ChessBoard* board, Position pos, Position moves[], int* count);
void getKnightMoves(ChessBoard* board, Position pos, Position moves[], int* count);
void getQueenMoves(ChessBoard* board, Position pos, Position moves[], int* count);
void getKingMoves(ChessBoard* board, Position pos, Position moves[], int* count);

// Funções de interface
void drawMenu(ChessGame* game, Menu* menu);
void handleMenuInput(ChessGame* game, Menu* menu, SDL_Event* event);
void drawUI(ChessGame* game);
void drawText(ChessGame* game, const char* text, int x, int y, SDL_Color color);

// Funções de áudio
bool initAudio(ChessGame* game);
void playSound(ChessGame* game, Mix_Chunk* sound);

// Funções de utilidade
bool isPositionValid(Position pos);
bool isPositionEmpty(ChessBoard* board, Position pos);
Piece* getPieceAt(ChessBoard* board, Position pos);
SDL_Color hexToColor(int hex);

#endif
