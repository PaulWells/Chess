#pragma once
#include "IMoveFinder.hpp"

class PawnMoveFinder : public ITypedMoveFinder
{
public:
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
    ChessPieceType GetPieceType() override;
private:

};
