#include "HumanPlayer.hpp"
#include "IChessPlayer.hpp"

#include <vector>

HumanPlayer::HumanPlayer()
{
    m_moveFinder = std::make_unique<MoveFinder>();
}

Move HumanPlayer::MakeMove(ChessBoard board, bool isBlackPlayer)
{
    std::unique_ptr<std::vector<Move>> moves = m_moveFinder->FindMoves(board, isBlackPlayer);

    for (int i = 0; i < moves->size(); i++)
    {
        std::cout << i << ": " <<  moves->at(i);
    }

    std::cout << " Choose a move: ";
    int moveIndex = -1;
    while(moveIndex < 0 || moveIndex >= moves->size())
    {
        std::cin >> moveIndex;
    }
    return moves->at(moveIndex);
}
