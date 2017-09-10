#pragma once
#include "ChessPiece.hpp"

static const int BOARD_WIDTH = 8;

typedef ChessPiece ChessBoard[BOARD_WIDTH][BOARD_WIDTH];

struct Square
{
    uint8_t row;
    uint8_t column;
};

namespace ChessBoardHelpers
{
    inline void ClearBoard(ChessBoard board)
    {
        for (int row = 0; row < BOARD_WIDTH; row++)
        {
            for (int column = 0; column < BOARD_WIDTH; column++)
            {
                board[row][column] = 0;

            }
        }
    }
    
    inline ChessPiece PieceAt(ChessBoard board, Square square)
    {
        return board[square.row][square.column];
    }
}
