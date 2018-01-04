#pragma once
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"

struct Move
{
    Square start;
    Square end;
    ChessPiece startState;
    ChessPiece endState;
    ChessPiece removedPiece;
    Square removedPieceSquare;
};

inline bool operator==(const Move& a, const Move& b)
{
    return (a.start == b.start &&
            a.end == b.end &&
            a.startState == b.startState &&
            a.endState == b.endState &&
            a.removedPiece == b.removedPiece &&
            a.removedPieceSquare == b.removedPieceSquare);
}

inline std::ostream& operator<<(std::ostream& os, const Move& move)
{
    os << move.startState << " takes " << move.removedPiece
       << "  " << "(" << move.start.row << ", " << move.start.column << ") -> (" << move.end.row << ", " << move.end.column << ")" << std::endl;

    return os;
}

namespace MoveHelpers
{
    inline Move CreateMove(ChessBoard board, Square square, Vector vector)
    {
        Move move;
        move.start = square;
        move.end = square + vector;
        move.startState = ChessBoardHelpers::PieceAt(board, square);
        move.endState = ChessPieceHelpers::MarkChessPieceAsMoved(move.startState);
        move.removedPiece = ChessBoardHelpers::PieceAt(board, move.end);
        move.removedPieceSquare = move.end;
        return move;
    }

    inline Move CopyMoveWithPromotion(Move move, uint8_t newPieceType)
    {
        Move promotionMove = move;
        promotionMove.endState = ChessPieceHelpers::ChangePieceType(move.endState, newPieceType);
        return promotionMove;
    }
};
