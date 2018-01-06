#pragma once

#include "IChessPlayer.hpp"
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include <memory>
#include "../moves/MoveFinder.hpp"

class RandomChessPlayer : public IChessPlayer
{
public:
    RandomChessPlayer();
    Move MakeMove(ChessBoard board, bool isBlackPlayer);

private:
    std::unique_ptr<MoveFinder> m_moveFinder;
};
