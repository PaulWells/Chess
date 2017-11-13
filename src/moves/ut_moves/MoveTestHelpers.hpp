#pragma once
#include "../../types/Move.hpp"

namespace MoveTestHelpers
{
    inline bool ContainsMoveWithSameEndPosition(std::vector<Move>* moves, Move move)
    {
        for (int i = 0; i < moves->size(); i++)
        {
            if (moves->at(i).end == move.end)
            {
                return true;
            }
        }
        return false;
    }
};
