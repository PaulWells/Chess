#include "GameManager.hpp"
#include "GameState.hpp"
#include "../types/ChessBoard.hpp"
#include "../moves/MoveFinder.hpp"
#include "../players/HumanPlayer.hpp"
#include "../players/RandomChessPlayer.hpp"

GameManager::GameManager()
{
    m_moveApplicator = std::make_unique<MoveApplicator>();
}

void GameManager::StartGame()
{
    bool isBlackTurn = false;
    std::unique_ptr<GameState> gameState = std::make_unique<GameState>();
    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();

    std::unique_ptr<IChessPlayer> humanPlayer = std::make_unique<HumanPlayer>();
    std::unique_ptr<IChessPlayer> randomPlayer = std::make_unique<RandomChessPlayer>();

    std::cout << gameState->m_board;

    while(true)
    {
        Move move;
        if (!isBlackTurn)
        {
            move = humanPlayer->MakeMove(gameState->m_board, isBlackTurn);
        }
        else
        {
            move = randomPlayer->MakeMove(gameState->m_board, isBlackTurn);
            std::cout << std::endl << move;
        }

        m_moveApplicator->ApplyMove(gameState->m_board, move);

        std::cout << gameState->m_board;

        isBlackTurn = !isBlackTurn;
    }



}
