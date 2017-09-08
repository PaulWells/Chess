#pragma once
#include "ChessPieceTypes.hpp"

namespace ChessPieceHelpers
{
    bool IsEmptySquare(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::EmptySquare);
    }

    bool IsPawn(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::Pawn);
    }

    bool IsKnight(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::Knight);
    }

    bool IsBishop(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::Bishop);
    }

    bool IsCastle(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::Castle);
    }

    bool IsQueen(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::Queen);
    }

    bool IsKing(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceTypeMask) == ChessPieceType::King);
    }
}
