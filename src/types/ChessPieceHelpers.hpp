#pragma once
#include "ChessPieceTypes.hpp"

namespace ChessPieceHelpers
{
    bool IsEmptySquare(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::EmptySquare);
    }

    bool IsPawn(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Pawn);
    }

    bool IsKnight(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Knight);
    }

    bool IsBishop(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Bishop);
    }

    bool IsCastle(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Castle);
    }

    bool IsQueen(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Queen);
    }

    bool IsKing(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::King);
    }

    static bool CompareAgainstMask(ChessPiece chessPiece, uint8_t mask)
    {
        return ((chessPiece & mask) == mask);
    }

    bool IsBlack(ChessPiece chessPiece)
    {
        return CompareAgainstMask(chessPiece, ChessPieceMask::Color);
    }

    bool IsWhite(ChessPiece chessPiece)
    {
        return !IsBlack(chessPiece);
    }

    bool HasMoved(ChessPiece chessPiece)
    {
        return CompareAgainstMask(chessPiece, ChessPieceMask::HasMoved);
    }

    bool HasNotMoved(ChessPiece chessPiece)
    {
        return !HasMoved(chessPiece);
    }

    bool JustPerformedEnPassant(ChessPiece chessPiece)
    {
        return CompareAgainstMask(chessPiece, ChessPieceMask::EnPassant);
    }

    ChessPiece MarkChessPieceAsMoved(ChessPiece piece)
    {
        return piece | ChessPieceMask::HasMoved;
    }

    ChessPiece MarkChessPieceAsEnPassant(ChessPiece piece)
    {
        return piece | ChessPieceMask::EnPassant;
    }

    ChessPiece MakeChessPiece(uint8_t pieceType, bool isBlack, bool hasMoved, bool enPassant)
    {
        ChessPiece piece = (isBlack ? pieceType | ChessPieceMask::Color : pieceType);
        if (hasMoved)
        {
            piece = MarkChessPieceAsMoved(piece);
        }
        if (enPassant)
        {
            piece = MarkChessPieceAsEnPassant(piece);
        }
        return piece;
    }
}
