#include "MoveApplicator.hpp"
#include "../types/ChessPiece.hpp"
#include "../types/ChessBoard.hpp"
#include "../moves/KingMoveFinder.hpp"

void MoveApplicator::ApplyMove(ChessBoard& board, Move& move)
{
    ChessPiece emptySquare = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);
    ChessBoardHelpers::SetPieceAt(board, move.start, emptySquare);
    ChessBoardHelpers::SetPieceAt(board, move.removedPieceSquare, emptySquare);
    ChessBoardHelpers::SetPieceAt(board, move.end, move.endState);

    bool movedPieceIsBlack = ChessPieceHelpers::IsBlack(move.startState);
    bool removedPieceIsBlack = ChessPieceHelpers::IsBlack(move.removedPiece);
    bool removedPieceType = ChessPieceHelpers::GetPieceType(move.removedPiece);
    bool removedPieceIsEmptySquare = (removedPieceType == ChessPieceTypes::EmptySquare);

    // If the removed piece is the same color as the moved piece then
    // this is a castling move.
    if (!removedPieceIsEmptySquare && movedPieceIsBlack == removedPieceIsBlack)
    {
        std::cout << "In if statement" << std::endl;
        Square castleSquare = KingMoveFinder::GetCastlePositionAfterCastling(move.end);
        ChessBoardHelpers::SetPieceAt(board, castleSquare, move.removedPiece);
    }
}
