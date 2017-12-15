#pragma once
#include "IMoveFinder.hpp"
#include "SlideMoveFinder.hpp"

class CastleMoveFinder : public ITypedMoveFinder
{
public:
    CastleMoveFinder();
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
    ChessPieceType GetPieceType() override;
private:
    std::unique_ptr<IMoveFinder> m_straightSlideMoveFinder;
};
