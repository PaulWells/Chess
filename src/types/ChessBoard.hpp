#pragma once
#include "ChessPiece.hpp"
#include "../util/TerminalColor.hpp"

static const int BOARD_WIDTH = 8;
static const int ROW_SCALE_FACTOR = 3;
static const int ROW_MIDDLE = (ROW_SCALE_FACTOR - 1) / 2;

typedef ChessPiece ChessBoard[BOARD_WIDTH][BOARD_WIDTH];

inline std::ostream& operator<<(std::ostream& os, const ChessBoard& board)
{
    os << std::endl;
    bool isBlack = false;
    for (int row = 0; row < BOARD_WIDTH * ROW_SCALE_FACTOR; row++)
    {
        bool isTextRow = (row % ROW_SCALE_FACTOR == ROW_MIDDLE);
        bool isFirstRow = (row % ROW_SCALE_FACTOR == 0);
        if (isFirstRow)
        {
            isBlack = !isBlack;
        }
        for (int column = 0; column < BOARD_WIDTH; column++)
        {
            isBlack = !isBlack;
            if (isBlack)
            {
                TerminalColor::SetBackgroundBlack();
            }
            else
            {
                TerminalColor::SetBackgroundWhite();
            }


            if (isTextRow)
            {
                std::cout << TerminalColor::Grey() << " ";
                std::cout << board[(row - ROW_MIDDLE) / ROW_SCALE_FACTOR][column];
            }
            else
            {
                std::cout << TerminalColor::Grey() << "\t" << TerminalColor::Reset();
            }
        }
        std::cout << std::endl;
    }
    // TerminalColor::SetBackgroundBlack();
    std::cout << TerminalColor::Reset();
    return os;
}

struct Vector
{
    int rowVector;
    int columnVector;
};

inline Vector operator+(const Vector& a, const Vector& b)
{
    return {
        a.rowVector + b.rowVector,
        a.columnVector + b.columnVector
    };
}

struct Square
{
    int row;
    int column;
};

inline bool operator==(const Square& a, const Square& b)
{
    return (a.row == b.row && a.column == b.column);
}

inline Square operator+(const Square& square, const Vector& vector)
{
    return {
        square.row + vector.rowVector,
        square.column + vector.columnVector
    };
}

inline std::ostream& operator<<(std::ostream& os, const Square& square)
{
    os << "Square: (" <<  square.row << ", " << square.column << ")" << std::endl;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << "Vector: (" <<  vector.rowVector << ", " << vector.columnVector << ")" << std::endl;
    return os;
}

inline Vector operator*(Vector a, const uint8_t& multiplier)
{
    a.rowVector = a.rowVector * multiplier;
    a.columnVector = a.columnVector * multiplier;
    return a;
}

namespace ChessBoardHelpers
{
    inline void ClearBoard(ChessBoard board)
    {
        for (int row = 0; row < BOARD_WIDTH; row++)
        {
            for (int column = 0; column < BOARD_WIDTH; column++)
            {
                board[row][column] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);
            }
        }
    }

    inline ChessPiece PieceAt(ChessBoard board, Square square)
    {
        return board[square.row][square.column];
    }

    inline void SetPieceAt(ChessBoard board, Square square, ChessPiece piece)
    {
        board[square.row][square.column] = piece;
    }

    inline bool OnBoard(Square square, Vector vector)
    {
        int8_t endRow = square.row + vector.rowVector;
        int8_t endColumn = square.column + vector.columnVector;
        return  (endRow >= 0 && endRow < BOARD_WIDTH && endColumn >= 0 && endColumn < BOARD_WIDTH);
    }

    inline bool OnBoard(Square square)
    {
        return  (square.row >= 0 && square.row < BOARD_WIDTH && square.column >= 0 && square.column < BOARD_WIDTH);
    }

    inline bool AreBoardsEqual(const ChessBoard& a, const ChessBoard& b)
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                if (a[i][j] != b[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
}
