#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "SlideMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"
#include "../util/FailFast.hpp"

IMoveFinder* SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType slideMoveType, int rangeLimit)
{
    switch(slideMoveType)
    {
        case SlideMoveType::Straight:
            return new SlideMoveFinder(straightSlideDirections, rangeLimit);
        break;
        case SlideMoveType::Diagonal:
            return new SlideMoveFinder(diagonalSlideDirections, rangeLimit);
        break;
        default:
            FAIL_FAST("Unexpected SlideMoveType");
        break;
    }
}

SlideMoveFinder::SlideMoveFinder(Vector slideDirections[NUMBER_SLIDE_DIRECTIONS], int rangeLimit)
{
    // Todo: Use memcpy or another utiltiy method to assign this Vector.
    m_slideDirections[0] = slideDirections[0];
    m_slideDirections[1] = slideDirections[1];
    m_slideDirections[2] = slideDirections[2];
    m_slideDirections[3] = slideDirections[3];
    m_rangeLimit = rangeLimit;
}

SlideMoveFinder::SlideMoveFinder()
{
}

std::unique_ptr<std::vector<Move>> SlideMoveFinder::FindMoves(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
    for (int i = 0; i < NUMBER_SLIDE_DIRECTIONS; i++ )
    {
        Vector direction = m_slideDirections[i];
        uint8_t distance = 0;
        bool isValidMove = true;
        bool moveCapturesOpposingPiece = false;

        // Continue searching for moves until an invalid move is found.
        // If a move would capture an opposing piece then it is valid but
        // the moving piece cannot move any farther.
        while (isValidMove && !moveCapturesOpposingPiece && distance < m_rangeLimit) {
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
