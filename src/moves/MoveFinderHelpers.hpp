#pragma once
#include "../types/ChessPiece.hpp"
#include "../types/ChessBoard.hpp"

namespace MoveFinderHelpers
{
    inline bool MoveIsValid(ChessBoard board, Square square, Vector vector)
    {
        bool isValidMove = ChessBoardHelpers::OnBoard(square, vector);
        if (isValidMove)
        {
            Square targetSquare = square + vector;
            ChessPiece targetPiece = ChessBoardHelpers::PieceAt(board, targetSquare);
            ChessPiece movingPiece = ChessBoardHelpers::PieceAt(board, square);
            isValidMove = ((ChessPieceHelpers::GetPieceType(targetPiece) == ChessPieceType::EmptySquare) ||
                           !ChessPieceHelpers::PiecesAreSameColor(movingPiece, targetPiece));
        }
        return isValidMove;
    }

    inline bool MoveCapturesOpposingPiece(ChessBoard board, Square square, Vector vector)
    {
        Square targetSquare = square + vector;
        ChessPiece targetPiece = ChessBoardHelpers::PieceAt(board, targetSquare);
        ChessPiece movingPiece = ChessBoardHelpers::PieceAt(board, square);
        bool moveCapturesOpposingPiece = ((ChessPieceHelpers::GetPieceType(targetPiece) != ChessPieceType::EmptySquare) &&
                                           !ChessPieceHelpers::PiecesAreSameColor(movingPiece, targetPiece));
        return moveCapturesOpposingPiece;
    }
};
