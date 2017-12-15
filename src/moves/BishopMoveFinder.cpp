#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "BishopMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

BishopMoveFinder::BishopMoveFinder()
{
    m_diagonalSlideMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Diagonal));
}

std::unique_ptr<std::vector<Move>> BishopMoveFinder::FindMoves(ChessBoard board, Square square)
{
    return m_diagonalSlideMoveFinder->FindMoves(board, square);
}

ChessPieceType BishopMoveFinder::GetPieceType()
{
    return ChessPieceTypes::Bishop;
}
