#pragma once
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"

struct Move
{
    Square start;
    Square end;
    ChessPiece startState;
    ChessPiece removedPiece;
};

inline bool operator==(const Move& a, const Move& b)
{
    return (a.start == b.start &&
            a.end == b.end &&
            a.startState == b.startState &&
            a.removedPiece == b.removedPiece);
}

inline std::ostream& operator<<(std::ostream& os, const Move& move)
{
    os << "Move:" << std::endl
       << "  " << move.startState << " takes " << move.removedPiece << std::endl
       << "  " << "(" << move.start.row << ", " << move.start.column << ") -> (" << move.end.row << ", " << move.end.column << ")" << std::endl;
    return os;
}

namespace MoveHelpers
{
    inline Move CreateMove(ChessBoard board, Square square, Distance distance)
    {
        Move move;
        move.start = square;
        move.end = ChessBoardHelpers::GetTargetSquare(square, distance);
        move.startState = ChessBoardHelpers::PieceAt(board, square);
        move.removedPiece = ChessBoardHelpers::PieceAt(board, move.end);
        return move;
    }
};
