#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "QueenMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

QueenMoveFinder::QueenMoveFinder()
{
    m_straightSlideMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Straight));
    m_diagonalSlideMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Diagonal));
}

static void AppendVector(std::vector<Move>* moves1, std::vector<Move>* moves2)
{
    for (int i = 0; i < moves2->size(); i++)
    {
        moves1->push_back(moves2->at(i));
    }
}

std::unique_ptr<std::vector<Move>> QueenMoveFinder::FindMoves(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = m_straightSlideMoveFinder->FindMoves(board, square);
    std::unique_ptr<std::vector<Move>> diagonalMoves = m_diagonalSlideMoveFinder->FindMoves(board, square);
    AppendVector(moves.get(), diagonalMoves.release());
    return std::move(moves);
}
