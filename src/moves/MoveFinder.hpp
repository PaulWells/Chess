#pragma once
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"

// The maximum number of moves for each piece is:
// Pawn: 4
// Knight: 8
// Bishop: 13
// Castle: 14
// Queen: 27
// King: 8

// Allocate an array of this size for each piece instead of using vector.
// Even if it does not make a large difference in terms of speed.  I at least
// know what the implementation is.

class MoveFinder
{
public:
    static MoveSet FindMoves(ChessBoard board, Square square);
private:
    static MoveSet GetKnightMoveSet(ChessBoard board, Square square);
    static bool ValidateKnightMove(ChessBoard board, Square square, Distance distance);
    static Move CreateKnightMove(ChessBoard board, Square square, Distance distance);
};
