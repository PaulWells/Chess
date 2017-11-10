#pragma once

class IMoveFinder
{
public:
    virtual std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) = 0;
};
