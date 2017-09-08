#pragma once
// This file specifies the types of the pieces used in Chess.

// Chess pieces.
// A chess piece is represented by a single byte.  The lower
// 3 bits specify the type of the piece (pawn, king etc).  The
// remaining bits are one-hot encoded with state information such
// as the color of a piece and whether that piece has already moved.
typedef unsigned char ChessPiece;

enum struct ChessPieceType : unsigned char
{
    EmptySquare = 0x0000,
    Pawn = 0x0001,
    Knight = 0x0002,
    Bishop = 0x0003,
    Castle = 0x0004,
    Queen = 0x0005,
    King = 0x0006
};

bool operator ==(ChessPieceType a, unsigned char b)
{
    return (static_cast<unsigned char>(a) == b);
}

bool operator ==(unsigned char a, ChessPieceType b)
{
    return (static_cast<unsigned char>(b) == a);
}


enum struct ChessPieceMask : unsigned char
{
    // 0 for white, 1 for black.
    ColorMask = 0x0080,

    // 1 if the piece has already moved this game.
    HasMovedMask = 0x0040,

    // 1 If the piece is a pawn and moved forward two spots on the previous turn.
    EnPassantMask = 0x0020,

    // If any of these bits are not zero then the square contains a chess piece.
    PieceTypeMask = 0x0007
};

bool operator &(ChessPieceMask a, unsigned char b)
{
    return (static_cast<unsigned char>(a) & b);
}

bool operator &(unsigned char a, ChessPieceMask b)
{
    return (static_cast<unsigned char>(b) & a);
}
