#pragma once
#include "../types/ChessPiece.hpp"
#include "../types/ChessBoard.hpp"

namespace MoveFinderHelpers
{
    inline bool MoveIsValid(ChessBoard board, Square square, Distance distance)
    {
        bool isValidMove = ChessBoardHelpers::OnBoard(square, distance);
        if (isValidMove)
        {
            Square targetSquare = ChessBoardHelpers::GetTargetSquare(square, distance);
            ChessPiece targetPiece = ChessBoardHelpers::PieceAt(board, targetSquare);
            ChessPiece movingPiece = ChessBoardHelpers::PieceAt(board, square);
            isValidMove = ((ChessPieceHelpers::GetPieceType(targetPiece) == ChessPieceType::EmptySquare) ||
                           !ChessPieceHelpers::PiecesAreSameColor(movingPiece, targetPiece));
        }
        return isValidMove;
    }
};
