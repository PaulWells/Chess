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

std::unique_ptr<std::vector<Move>> QueenMoveFinder::FindMoves(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = m_straightSlideMoveFinder->FindMoves(board, square);
    std::unique_ptr<std::vector<Move>> diagonalMoves = m_diagonalSlideMoveFinder->FindMoves(board, square);
    moves->insert(moves->end(), diagonalMoves->begin(), diagonalMoves->end());
    return std::move(moves);
}

ChessPieceType QueenMoveFinder::GetPieceType()
{
    return ChessPieceTypes::Queen;
}
