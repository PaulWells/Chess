#pragma once
#include "../types/ChessBoard.hpp"

class GameState
{
public:
    GameState();
    ChessBoard m_board;
    Square m_whiteKingSquare;
    Square m_blackKingSquare;
    Square m_enPassantSquare;

private:
    void InitializeChessBoard();
};
