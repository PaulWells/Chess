#pragma once
#include "IMoveFinder.hpp"

class StraightSlideMoveFinder : public IMoveFinder
{
public:
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
private:
};
