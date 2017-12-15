#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "CastleMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

CastleMoveFinder::CastleMoveFinder()
{
    m_straightSlideMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Straight));
}

std::unique_ptr<std::vector<Move>> CastleMoveFinder::FindMoves(ChessBoard board, Square square)
{
    return m_straightSlideMoveFinder->FindMoves(board, square);
}

ChessPieceType CastleMoveFinder::GetPieceType()
{
    return ChessPieceTypes::Castle;
}
