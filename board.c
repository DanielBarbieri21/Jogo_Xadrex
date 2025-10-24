#include "chess_engine.h"

void initBoard(ChessBoard* board) {
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
    
    // Configurar estado inicial
    board->isSelected = false;
    board->currentPlayer = COLOR_WHITE_PIECE;
    board->moveCount = 0;
    
    // Colocar peças de exemplo para demonstração
    // Torre
    board->board[0][0].type = PIECE_ROOK;
    board->board[0][0].color = COLOR_WHITE_PIECE;
    
    // Bispo
    board->board[1][1].type = PIECE_BISHOP;
    board->board[1][1].color = COLOR_WHITE_PIECE;
    
    // Rainha
    board->board[2][2].type = PIECE_QUEEN;
    board->board[2][2].color = COLOR_WHITE_PIECE;
    
    // Cavalo
    board->board[3][3].type = PIECE_KNIGHT;
    board->board[3][3].color = COLOR_WHITE_PIECE;
}

void drawBoard(ChessGame* game) {
    // Desenhar fundo do tabuleiro
    SDL_Rect boardRect = {100, 100, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE};
    SDL_SetRenderDrawColor(game->renderer, 139, 69, 19, 255);
    SDL_RenderFillRect(game->renderer, &boardRect);
    
    // Desenhar quadrados
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            SDL_Color squareColor;
            if ((i + j) % 2 == 0) {
                squareColor = COLOR_LIGHT_BROWN;
            } else {
                squareColor = COLOR_DARK_BROWN;
            }
            
            // Destacar quadrado selecionado
            if (game->board.isSelected && 
                game->board.selected.x == i && game->board.selected.y == j) {
                squareColor = COLOR_SELECTED;
            }
            
            drawSquare(game, i, j, squareColor);
            
            // Desenhar peça
            Piece piece = game->board.board[i][j];
            if (piece.type != PIECE_NONE) {
                drawPiece(game, piece, i, j);
            }
        }
    }
    
    // Mostrar movimentos possíveis
    if (game->showMoves && game->board.isSelected) {
        Position moves[64];
        int moveCount = 0;
        getPossibleMoves(&game->board, game->board.selected, moves, &moveCount);
        
        for (int i = 0; i < moveCount; i++) {
            SDL_Rect moveRect = {
                100 + moves[i].x * SQUARE_SIZE + 5,
                100 + moves[i].y * SQUARE_SIZE + 5,
                SQUARE_SIZE - 10,
                SQUARE_SIZE - 10
            };
            SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 100);
            SDL_RenderFillRect(game->renderer, &moveRect);
        }
    }
}

void drawSquare(ChessGame* game, int x, int y, SDL_Color color) {
    SDL_Rect rect = {
        100 + x * SQUARE_SIZE,
        100 + y * SQUARE_SIZE,
        SQUARE_SIZE,
        SQUARE_SIZE
    };
    
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(game->renderer, &rect);
    
    // Borda do quadrado
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(game->renderer, &rect);
}

void drawPiece(ChessGame* game, Piece piece, int x, int y) {
    int centerX = 100 + x * SQUARE_SIZE + SQUARE_SIZE / 2;
    int centerY = 100 + y * SQUARE_SIZE + SQUARE_SIZE / 2;
    int radius = SQUARE_SIZE / 3;
    
    // Cor da peça
    SDL_Color pieceColor = piece.color == COLOR_WHITE_PIECE ? COLOR_WHITE : COLOR_BLACK;
    SDL_SetRenderDrawColor(game->renderer, pieceColor.r, pieceColor.g, pieceColor.b, pieceColor.a);
    
    // Desenhar círculo base
    for (int i = 0; i < radius; i++) {
        for (int j = 0; j < radius; j++) {
            if (i * i + j * j <= radius * radius) {
                SDL_RenderDrawPoint(game->renderer, centerX + i, centerY + j);
                SDL_RenderDrawPoint(game->renderer, centerX - i, centerY + j);
                SDL_RenderDrawPoint(game->renderer, centerX + i, centerY - j);
                SDL_RenderDrawPoint(game->renderer, centerX - i, centerY - j);
            }
        }
    }
    
    // Desenhar símbolo da peça
    SDL_Color symbolColor = piece.color == COLOR_WHITE_PIECE ? COLOR_BLACK : COLOR_WHITE;
    drawText(game, getPieceSymbol(piece.type), centerX - 10, centerY - 10, symbolColor);
}

const char* getPieceSymbol(PieceType type) {
    switch (type) {
        case PIECE_PAWN: return "P";
        case PIECE_ROOK: return "R";
        case PIECE_KNIGHT: return "N";
        case PIECE_BISHOP: return "B";
        case PIECE_QUEEN: return "Q";
        case PIECE_KING: return "K";
        default: return "";
    }
}

bool isValidMove(ChessBoard* board, Position from, Position to) {
    if (!isPositionValid(from) || !isPositionValid(to)) {
        return false;
    }
    
    Piece* fromPiece = getPieceAt(board, from);
    Piece* toPiece = getPieceAt(board, to);
    
    if (!fromPiece || fromPiece->type == PIECE_NONE) {
        return false;
    }
    
    // Verificar se não está capturando peça da mesma cor
    if (toPiece && toPiece->type != PIECE_NONE && toPiece->color == fromPiece->color) {
        return false;
    }
    
    // Verificar movimento específico da peça
    Position moves[64];
    int moveCount = 0;
    getPossibleMoves(board, from, moves, &moveCount);
    
    for (int i = 0; i < moveCount; i++) {
        if (moves[i].x == to.x && moves[i].y == to.y) {
            return true;
        }
    }
    
    return false;
}

void makeMove(ChessBoard* board, Position from, Position to) {
    Piece* fromPiece = getPieceAt(board, from);
    Piece* toPiece = getPieceAt(board, to);
    
    if (fromPiece && toPiece) {
        // Mover peça
        *toPiece = *fromPiece;
        toPiece->pos = to;
        toPiece->hasMoved = true;
        
        // Limpar posição original
        fromPiece->type = PIECE_NONE;
        fromPiece->color = COLOR_WHITE_PIECE;
        fromPiece->hasMoved = false;
        
        board->moveCount++;
        board->currentPlayer = !board->currentPlayer;
    }
}

void getPossibleMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    
    if (!piece || piece->type == PIECE_NONE) {
        return;
    }
    
    switch (piece->type) {
        case PIECE_PAWN:
            getPawnMoves(board, pos, moves, count);
            break;
        case PIECE_ROOK:
            getRookMoves(board, pos, moves, count);
            break;
        case PIECE_KNIGHT:
            getKnightMoves(board, pos, moves, count);
            break;
        case PIECE_BISHOP:
            getBishopMoves(board, pos, moves, count);
            break;
        case PIECE_QUEEN:
            getQueenMoves(board, pos, moves, count);
            break;
        case PIECE_KING:
            getKingMoves(board, pos, moves, count);
            break;
    }
}

bool isPositionValid(Position pos) {
    return pos.x >= 0 && pos.x < BOARD_SIZE && pos.y >= 0 && pos.y < BOARD_SIZE;
}

bool isPositionEmpty(ChessBoard* board, Position pos) {
    if (!isPositionValid(pos)) return false;
    return board->board[pos.x][pos.y].type == PIECE_NONE;
}

Piece* getPieceAt(ChessBoard* board, Position pos) {
    if (!isPositionValid(pos)) return NULL;
    return &board->board[pos.x][pos.y];
}
