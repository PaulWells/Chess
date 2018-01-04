#pragma once

#include "IMoveFinder.hpp"

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
    MoveFinder();
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square);
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, bool forBlack);
private:
    std::unique_ptr<ITypedMoveFinder> m_knightMoveFinder;
    std::unique_ptr<ITypedMoveFinder> m_castleMoveFinder;
    std::unique_ptr<ITypedMoveFinder> m_bishopMoveFinder;
    std::unique_ptr<ITypedMoveFinder> m_queenMoveFinder;
    std::unique_ptr<ITypedMoveFinder> m_pawnMoveFinder;
    std::unique_ptr<ITypedMoveFinder> m_kingMoveFinder;
};
