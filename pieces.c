#include "chess_engine.h"

void getPawnMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    if (!piece) return;
    
    int direction = (piece->color == COLOR_WHITE_PIECE) ? -1 : 1;
    int startRow = (piece->color == COLOR_WHITE_PIECE) ? 6 : 1;
    
    // Movimento para frente
    Position forward = {pos.x, pos.y + direction};
    if (isPositionValid(forward) && isPositionEmpty(board, forward)) {
        moves[(*count)++] = forward;
        
        // Movimento duplo do peão na primeira jogada
        if (pos.y == startRow) {
            Position doubleForward = {pos.x, pos.y + 2 * direction};
            if (isPositionValid(doubleForward) && isPositionEmpty(board, doubleForward)) {
                moves[(*count)++] = doubleForward;
            }
        }
    }
    
    // Captura diagonal
    for (int dx = -1; dx <= 1; dx += 2) {
        Position capture = {pos.x + dx, pos.y + direction};
        if (isPositionValid(capture)) {
            Piece* targetPiece = getPieceAt(board, capture);
            if (targetPiece && targetPiece->type != PIECE_NONE && targetPiece->color != piece->color) {
                moves[(*count)++] = capture;
            }
        }
    }
}

void getRookMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    if (!piece) return;
    
    // Movimentos horizontais e verticais
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    for (int d = 0; d < 4; d++) {
        for (int i = 1; i < BOARD_SIZE; i++) {
            Position newPos = {pos.x + i * directions[d][0], pos.y + i * directions[d][1]};
            
            if (!isPositionValid(newPos)) break;
            
            Piece* targetPiece = getPieceAt(board, newPos);
            if (targetPiece && targetPiece->type != PIECE_NONE) {
                if (targetPiece->color != piece->color) {
                    moves[(*count)++] = newPos;
                }
                break;
            }
            
            moves[(*count)++] = newPos;
        }
    }
}

void getBishopMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    if (!piece) return;
    
    // Movimentos diagonais
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    
    for (int d = 0; d < 4; d++) {
        for (int i = 1; i < BOARD_SIZE; i++) {
            Position newPos = {pos.x + i * directions[d][0], pos.y + i * directions[d][1]};
            
            if (!isPositionValid(newPos)) break;
            
            Piece* targetPiece = getPieceAt(board, newPos);
            if (targetPiece && targetPiece->type != PIECE_NONE) {
                if (targetPiece->color != piece->color) {
                    moves[(*count)++] = newPos;
                }
                break;
            }
            
            moves[(*count)++] = newPos;
        }
    }
}

void getKnightMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    if (!piece) return;
    
    // Movimentos em L do cavalo
    int knightMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    for (int i = 0; i < 8; i++) {
        Position newPos = {pos.x + knightMoves[i][0], pos.y + knightMoves[i][1]};
        
        if (isPositionValid(newPos)) {
            Piece* targetPiece = getPieceAt(board, newPos);
            if (!targetPiece || targetPiece->type == PIECE_NONE || targetPiece->color != piece->color) {
                moves[(*count)++] = newPos;
            }
        }
    }
}

void getQueenMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    if (!piece) return;
    
    // A rainha combina movimentos da torre e do bispo
    getRookMoves(board, pos, moves, count);
    int rookCount = *count;
    
    Position bishopMoves[64];
    int bishopCount = 0;
    getBishopMoves(board, pos, bishopMoves, &bishopCount);
    
    // Adicionar movimentos do bispo
    for (int i = 0; i < bishopCount; i++) {
        moves[(*count)++] = bishopMoves[i];
    }
}

void getKingMoves(ChessBoard* board, Position pos, Position moves[], int* count) {
    *count = 0;
    Piece* piece = getPieceAt(board, pos);
    if (!piece) return;
    
    // Movimentos do rei (uma casa em qualquer direção)
    int directions[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    
    for (int d = 0; d < 8; d++) {
        Position newPos = {pos.x + directions[d][0], pos.y + directions[d][1]};
        
        if (isPositionValid(newPos)) {
            Piece* targetPiece = getPieceAt(board, newPos);
            if (!targetPiece || targetPiece->type == PIECE_NONE || targetPiece->color != piece->color) {
                moves[(*count)++] = newPos;
            }
        }
    }
}
