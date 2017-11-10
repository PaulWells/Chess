#pragma once
#include "IMoveFinder.hpp"

class CastleMoveFinder : public IMoveFinder
{
public:
    CastleMoveFinder();
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
private:
    // Castle will have a move finder for normal moves and a move finder
    // for castling.
    std::unique_ptr<IMoveFinder> m_straightSlideMoveFinder;
};
