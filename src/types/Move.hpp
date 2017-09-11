#pragma once
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"

struct Move
{
    Square start;
    Square end;
    ChessPiece startState;
    ChessPiece removedPiece;
};

inline bool operator==(const Move& a, const Move& b)
{
    return (a.start == b.start &&
            a.end == b.end &&
            a.startState == b.startState &&
            a.removedPiece == b.removedPiece);
}

struct MoveSet
{
    Move* moves;
    int count;
};
