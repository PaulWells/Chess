#pragma once
#include "ChessPiece.hpp"

static const int BOARD_WIDTH = 8;

typedef ChessPiece ChessBoard[BOARD_WIDTH][BOARD_WIDTH];

struct Square
{
    int row;
    int column;
};

inline bool operator==(const Square& a, const Square& b)
{
    return (a.row == b.row && a.row == b.row);
}

struct Distance
{
    int rowDistance;
    int columnDistance;
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

    inline bool OnBoard(Square square, Distance distance)
    {
        int8_t endRow = square.row + distance.rowDistance;
        int8_t endColumn = square.column + distance.columnDistance;
        return  (endRow >= 0 && endRow < 8 && endColumn >= 0 && endColumn < 8);
    }

    // This method should only be used when we already know that the
    // target Square is on the board.  Otherwise a int8_t may be cast to a uint8_t
    inline Square GetTargetSquare(Square square, Distance distance)
    {
        return { square.row + distance.rowDistance, square.column + distance.columnDistance };
    }
}
