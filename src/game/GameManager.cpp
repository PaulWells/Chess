#include "GameManager.hpp"
#include "GameState.hpp"
#include "../types/ChessBoard.hpp"

void GameManager::StartGame()
{
    bool isBlackTurn = false;
    std::unique_ptr<GameState> gameState = std::make_unique<GameState>();
    std::cout << gameState->m_board;

}
