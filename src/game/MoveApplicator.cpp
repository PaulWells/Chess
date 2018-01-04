#include "MoveApplicator.hpp"
#include "../types/ChessPiece.hpp"
#include "../types/ChessBoard.hpp"

void MoveApplicator::ApplyMove(ChessBoard& board, Move& move)
{
    ChessPiece emptySquare = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);
    ChessBoardHelpers::SetPieceAt(board, move.start, emptySquare);
    ChessBoardHelpers::SetPieceAt(board, move.removedPieceSquare, emptySquare);
    ChessBoardHelpers::SetPieceAt(board, move.end, move.endState);
}
