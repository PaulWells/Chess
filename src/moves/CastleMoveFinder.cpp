#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "SlideMoveFinder.hpp"
#include "CastleMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"


CastleMoveFinder::CastleMoveFinder()
{
    m_slideMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Straight));
}

std::unique_ptr<std::vector<Move>> CastleMoveFinder::FindMoves(ChessBoard board, Square square)
{
    return m_slideMoveFinder->FindMoves(board, square);
}
