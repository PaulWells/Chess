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
    const uint8_t EnPassant = 0x20;

    // If any of these bits are not zero then the square contains a chess piece.
    const uint8_t PieceType = 0x07;
};
