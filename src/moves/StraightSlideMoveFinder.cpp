#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "StraightSlideMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

static const uint8_t NUMBER_STRAING_SLIDE_DIRECTIONS = 4;
static Vector straightSlideDirections[NUMBER_STRAING_SLIDE_DIRECTIONS] = {
    {  0,  1 },
    {  1,  0 },
    {  0, -1 },
    { -1,  0 },
};

std::unique_ptr<std::vector<Move>> StraightSlideMoveFinder::FindMoves(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = std::make_unique<std::vector<Move>>(std::vector<Move>());

    for (int i = 0; i < NUMBER_STRAING_SLIDE_DIRECTIONS; i++ )
    {
        Vector direction = straightSlideDirections[i];
        uint8_t distance = 0;
        bool isValidMove = true;
        bool moveCapturesOpposingPiece = false;

        // Continue searching for moves until an invalid move is found.
        // If a move would capture an opposing piece then it is valid but
        // the moving piece cannot move any farther.
        while (isValidMove && !moveCapturesOpposingPiece) {
            distance++;
            Vector vector = direction * distance;
            isValidMove = MoveFinderHelpers::MoveIsValid(board, square, vector);
            if (isValidMove)
            {
                Move move = MoveHelpers::CreateMove(board, square, vector);
                moves->push_back(move);
            }
            moveCapturesOpposingPiece = MoveFinderHelpers::MoveCapturesOpposingPiece(board, square, vector);
        }
    }
    return std::move(moves);
}
