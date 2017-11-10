#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "KnightMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

static const uint8_t MAX_KNIGHT_MOVES = 8;
static Distance knightDistances[MAX_KNIGHT_MOVES] = {
    {  2,  1 },
    {  2, -1 },
    {  1,  2 },
    { -1,  2 },
    { -2,  1 },
    { -2, -1 },
    {  1, -2 },
    { -1, -2 }
};

std::unique_ptr<std::vector<Move>> KnightMoveFinder::FindMoves(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
    moves->reserve(MAX_KNIGHT_MOVES);
    for (int i = 0; i < MAX_KNIGHT_MOVES; i++ )
    {
        if (MoveFinderHelpers::MoveIsValid(board, square, knightDistances[i]))
        {
            Move move = MoveHelpers::CreateMove(board, square, knightDistances[i]);
            moves->push_back(move);
        }
    }
    return std::move(moves);
}
