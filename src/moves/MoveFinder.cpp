#include <iostream>
#include "MoveFinder.hpp"
#include "../types/ChessBoard.hpp"
#include "../types/ChessPiece.hpp"

// The square represents the piece to find moves for.
MoveSet MoveFinder::FindMoves(ChessBoard board, Square square)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    MoveSet moveSet;

    switch (ChessPieceHelpers::GetPieceType(piece))
    {
        case ChessPieceType::EmptySquare:
            moveSet = { nullptr, 0 };
        break;
        default:
            moveSet = { nullptr, 0 };
            std::cerr << "MoveFinder::FindMoves switch (ChessPieceHelpers::GetPieceType(piece)) default should not be hit" << std::endl;
    }
    return moveSet;
}
