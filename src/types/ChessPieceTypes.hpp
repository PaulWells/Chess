// This file specifies the struct types used in Chess.

// Chess pieces.
// A chess piece is represented by a single byte.  The lower
// 3 bits specify the type of the piece (pawn, king etc).  The
// remaining bits are one-hot encoded with state information such
// as the color of a piece and whether that piece has already moved.
const unsigned char emptySquare = 0x00;
const unsigned char pawn = 0x01;
const unsigned char knight = 0x02;
const unsigned char bishop = 0x03;
const unsigned char castle = 0x04;
const unsigned char queen = 0x05;
const unsigned char king = 0x06;

// 0 for white, 1 for black.
const unsigned char colorMask = 0x80;

// 1 if the piece has already moved this game.
const unsigned char hasMovedMask = 0x40;

// 1 If the piece is a pawn and moved forward two spots on the previous turn.
const unsigned char enPassantMask = 0x20;

// If any of these bits are not zero then the square contains a chess piece.
const unsigned char pieceTypeMask = 0x07;
