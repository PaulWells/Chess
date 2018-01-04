#pragma once
#include <iostream>
#include "../util/TerminalColor.hpp"
// This file specifies the types of the pieces used in Chess.

// Chess pieces.
// A chess piece is represented by a single byte.  The lower
// 3 bits specify the type of the piece (pawn, king etc).  The
// remaining bits are one-hot encoded with state information such
// as the color of a piece and whether that piece has already moved.
typedef uint8_t ChessPiece;
typedef uint8_t ChessPieceType;

namespace ChessPieceTypes
{
    const ChessPieceType EmptySquare = 0x00;
    const ChessPieceType Pawn = 0x01;
    const ChessPieceType Knight = 0x02;
    const ChessPieceType Bishop = 0x03;
    const ChessPieceType Castle = 0x04;
    const ChessPieceType Queen = 0x05;
    const ChessPieceType King = 0x06;
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
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::EmptySquare);
    }

    inline bool IsPawn(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::Pawn);
    }

    inline bool IsKnight(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::Knight);
    }

    inline bool IsBishop(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::Bishop);
    }

    inline bool IsCastle(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::Castle);
    }

    inline bool IsQueen(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::Queen);
    }

    inline bool IsKing(ChessPiece chessPiece)
    {
        return ((chessPiece & ChessPieceMask::PieceType) == ChessPieceTypes::King);
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

    inline ChessPiece ClearMovedTwoSpaces(ChessPiece piece)
    {
        return piece & ~ChessPieceMask::JustMovedTwoSpaces;
    }

    inline ChessPiece ClearPieceType(ChessPiece piece)
    {
        return piece & ~ChessPieceMask::PieceType;
    }

    inline ChessPiece SetPieceType(ChessPiece piece, uint8_t pieceType)
    {
        return piece | pieceType;
    }

    inline ChessPiece SetPieceAsBlack(ChessPiece piece)
    {
        return piece | ChessPieceMask::Color;
    }

    inline ChessPiece MakeChessPiece(uint8_t pieceType, bool isBlack, bool hasMoved, bool movedTwoSpaces)
    {
        ChessPiece piece = { 0 };
        piece = SetPieceType(piece, pieceType);

        if (isBlack)
        {
            piece = SetPieceAsBlack(piece);
        }

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

    inline ChessPiece ChangePieceType(ChessPiece piece, uint8_t pieceType)
    {
        ChessPiece newPiece = ChessPieceHelpers::ClearPieceType(piece);
        return ChessPieceHelpers::SetPieceType(newPiece, pieceType);
    }

    inline uint8_t GetPieceType(ChessPiece piece)
    {
        return (piece & ChessPieceMask::PieceType);
    }

    inline bool PiecesAreSameColor(ChessPiece piece1, ChessPiece piece2)
    {
        return (IsBlack(piece1) == IsBlack(piece2) &&
               GetPieceType(piece1) != ChessPieceTypes::EmptySquare &&
               GetPieceType(piece2) != ChessPieceTypes::EmptySquare);
    }

    inline std::string PieceTypeToString(uint8_t pieceType)
    {
        std::string pieceTypeAsString;
        switch(pieceType)
        {
            case ChessPieceTypes::EmptySquare:
                pieceTypeAsString.assign("      \t");
            break;
            case ChessPieceTypes::Pawn:
                pieceTypeAsString.assign("Pawn  \t");
            break;
            case ChessPieceTypes::Knight:
                pieceTypeAsString.assign("Knight\t");
            break;
            case ChessPieceTypes::Bishop:
                pieceTypeAsString.assign("Bishop\t");
            break;
            case ChessPieceTypes::Castle:
                pieceTypeAsString.assign("Castle\t");
            break;
            case ChessPieceTypes::Queen:
                pieceTypeAsString.assign("Queen\t");
            break;
            case ChessPieceTypes::King:
                pieceTypeAsString.assign("King\t");
            break;
            default:
            std::cerr << "Unidentified PieceType: PieceTypeToString";
        }
        return pieceTypeAsString;
    }
};

inline std::ostream& operator<<(std::ostream& os, const ChessPiece& piece)
{
    uint8_t type = ChessPieceHelpers::GetPieceType(piece);
    std::string typeAsString = (ChessPieceHelpers::PieceTypeToString(type));
    if (type == ChessPieceTypes::EmptySquare)
    {
        os << TerminalColor::Brown();
    }
    else if (ChessPieceHelpers::IsBlack(piece))
    {
        os << TerminalColor::DarkBlue();
    }
    else
    {
        os << TerminalColor::Grey();
    }
    os << typeAsString << TerminalColor::Reset();
    return os;
}
