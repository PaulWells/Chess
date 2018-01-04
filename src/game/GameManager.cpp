#include "GameManager.hpp"
#include "GameState.hpp"
#include "../types/ChessBoard.hpp"
#include "../moves/MoveFinder.hpp"

GameManager::GameManager()
{
    m_moveApplicator = std::make_unique<MoveApplicator>();
}

void GameManager::StartGame()
{
    bool isBlackTurn = false;
    std::unique_ptr<GameState> gameState = std::make_unique<GameState>();
    std::cout << gameState->m_board;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(gameState->m_board, false /*forBlack*/);

    for (int i = 0; i < moves->size(); i++)
    {
        std::cout << i << ": " <<  moves->at(i);
    }

    std::cout << " Choose a move: ";
    int moveIndex;
    std::cin >> moveIndex;

    m_moveApplicator->ApplyMove(gameState->m_board, moves->at(moveIndex));

    std::cout << gameState->m_board;


}
