#pragma once

#include "../types/Move.hpp"
#include "../types/ChessBoard.hpp"

class MoveApplicator
{
public:
    void ApplyMove(ChessBoard& board, Move& move);
};
