#pragma once

#include "IChessPlayer.hpp"
#include "../types/Move.hpp"
#include "../types/ChessBoard.hpp"
#include "../moves/MoveFinder.hpp"
#include <memory>

class HumanPlayer : public IChessPlayer
{
public:
    HumanPlayer();
    Move MakeMove(ChessBoard board, bool isBlackPlayer);

private:
    std::unique_ptr<MoveFinder> m_moveFinder;

};
