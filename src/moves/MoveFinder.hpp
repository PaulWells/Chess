#pragma once
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include <vector>

// The maximum number of moves for each piece is:
// Pawn: 4
// Knight: 8
// Bishop: 13
// Castle: 14
// Queen: 27
// King: 8

// Start by using the std::vector object.  To implement a truly data driven
// approach all memory will have to be preallocated and a custom allocator used.

class MoveFinder
{
public:
    static std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square);
private:
    static std::unique_ptr<std::vector<Move>> GetKnightMoveSet(ChessBoard board, Square square);
    static bool KnightMoveIsValid(ChessBoard board, Square square, Distance distance);
    static Move CreateKnightMove(ChessBoard board, Square square, Distance distance);
};
