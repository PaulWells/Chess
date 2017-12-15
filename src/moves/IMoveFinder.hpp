#pragma once
#include <vector>
#include "../types/Move.hpp"

#include "../types/ChessPiece.hpp"

class IMoveFinder
{
public:
    virtual std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) = 0;
};

// For move finders that represent a specific piece type, we want to know that piece type
// when determining if a square is under attack or not.
class ITypedMoveFinder : public IMoveFinder
{
public:
    virtual ChessPieceType GetPieceType() = 0;
};
