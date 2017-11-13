#pragma once
#include "IMoveFinder.hpp"
#include "SlideMoveFinder.hpp"

class QueenMoveFinder : public IMoveFinder
{
public:
    QueenMoveFinder();
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
private:
    std::unique_ptr<IMoveFinder> m_straightSlideMoveFinder;
    std::unique_ptr<IMoveFinder> m_diagonalSlideMoveFinder;
};
