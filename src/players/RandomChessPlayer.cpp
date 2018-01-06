#include "RandomChessPlayer.hpp"

#include <vector>

RandomChessPlayer::RandomChessPlayer()
{
    m_moveFinder = std::make_unique<MoveFinder>();
}

Move RandomChessPlayer::MakeMove(ChessBoard board, bool isBlackPlayer)
{
    std::unique_ptr<std::vector<Move>> moves = m_moveFinder->FindMoves(board, isBlackPlayer);

    int moveIndex = rand() % moves->size();

    return moves->at(moveIndex);
}
