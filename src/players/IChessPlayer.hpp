#pragma once

#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"

class IChessPlayer
{
public:
    virtual Move MakeMove(ChessBoard board, bool isBlackPlayer) = 0;
};
