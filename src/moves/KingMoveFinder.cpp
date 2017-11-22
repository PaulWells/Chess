#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "KingMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

KingMoveFinder::KingMoveFinder()
{
    m_straightSlideMoveFinder = std::unique_ptr<IMoveFinder>(
        SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Straight, 1 /*rangeLimit*/));

    m_diagonalSlideMoveFinder = std::unique_ptr<IMoveFinder>(
        SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Diagonal, 1 /*rangeLimit*/));
}

std::unique_ptr<std::vector<Move>> KingMoveFinder::FindMoves(ChessBoard board, Square square)
{
    // Todo add castling Moves.
    std::unique_ptr<std::vector<Move>> moves = m_straightSlideMoveFinder->FindMoves(board, square);
    std::unique_ptr<std::vector<Move>> diagonalMoves = m_diagonalSlideMoveFinder->FindMoves(board, square);
    moves->insert(moves->end(), diagonalMoves->begin(), diagonalMoves->end());
    return std::move(moves);
}
