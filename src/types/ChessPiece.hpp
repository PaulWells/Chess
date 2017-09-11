#pragma once
#include <iostream>
// This file specifies the types of the pieces used in Chess.

// Chess pieces.
// A chess piece is represented by a single byte.  The lower
// 3 bits specify the type of the piece (pawn, king etc).  The
// remaining bits are one-hot encoded with state information such
// as the color of a piece and whether that piece has already moved.
typedef uint8_t ChessPiece;

namespace ChessPieceType
{
    const uint8_t EmptySquare = 0x00;
    const uint8_t Pawn = 0x01;
    const uint8_t Knight = 0x02;
    const uint8_t Bishop = 0x03;
    const uint8_t Castle = 0x04;
    const uint8_t Queen = 0x05;
    const uint8_t King = 0x06;
};

namespace ChessPieceMask
{
    // 0 for white, 1 for black.
    const uint8_t Color = 0x80;

    // 1 if the piece has already moved this game.
    const uint8_t HasMoved = 0x40;

    // 1 If the piece is a pawn and moved forward two spots on the previous turn.
    const uint8_t JustMovedTwoSpaces = 0x20;

    // If any of these bits are not zero then the square contains a chess piece.
    const uint8_t PieceType = 0x07;
};


namespace ChessPieceHelpers
{
    inline bool IsEmptySquare(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::EmptySquare);
    }

    inline bool IsPawn(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Pawn);
    }

    inline bool IsKnight(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Knight);
    }

    inline bool IsBishop(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Bishop);
    }

    inline bool IsCastle(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Castle);
    }

    inline bool IsQueen(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::Queen);
    }

    inline bool IsKing(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceType::King);
    }

    static bool CompareAgainstMask(ChessPiece chessPiece, uint8_t mask)
    {
        return ((chessPiece & mask) == mask);
    }

    inline bool IsBlack(ChessPiece chessPiece)
    {
        return CompareAgainstMask(chessPiece, ChessPieceMask::Color);
    }

    inline bool IsWhite(ChessPiece chessPiece)
    {
        return !IsBlack(chessPiece);
    }

    inline bool HasMoved(ChessPiece chessPiece)
    {
        return CompareAgainstMask(chessPiece, ChessPieceMask::HasMoved);
    }

    inline bool HasNotMoved(ChessPiece chessPiece)
    {
        return !HasMoved(chessPiece);
    }

    inline bool JustMovedTwoSpaces(ChessPiece chessPiece)
    {
        return CompareAgainstMask(chessPiece, ChessPieceMask::JustMovedTwoSpaces);
    }

    inline ChessPiece MarkChessPieceAsMoved(ChessPiece piece)
    {
        return piece | ChessPieceMask::HasMoved;
    }

    inline ChessPiece MarkPawnAsMovedTwoSpaces(ChessPiece piece)
    {
        return piece | ChessPieceMask::JustMovedTwoSpaces;
    }

    inline ChessPiece MakeChessPiece(uint8_t pieceType, bool isBlack, bool hasMoved, bool movedTwoSpaces)
    {
        ChessPiece piece = (isBlack ? pieceType | ChessPieceMask::Color : pieceType);
        if (hasMoved)
        {
            piece = MarkChessPieceAsMoved(piece);
        }
        if (movedTwoSpaces)
        {
            piece = MarkPawnAsMovedTwoSpaces(piece);
        }
        return piece;
    }

    inline uint8_t GetPieceType(ChessPiece piece)
    {
        return (piece & ChessPieceMask::PieceType);
    }

    inline bool SameColor(ChessPiece piece1, ChessPiece piece2)
    {
        return (IsBlack(piece1) == IsBlack(piece2) &&
               GetPieceType(piece1) != ChessPieceType::EmptySquare &&
               GetPieceType(piece2) != ChessPieceType::EmptySquare);
    }
};
