#pragma once
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"

struct Move
{
    Square start;
    Square end;
    ChessPiece startState;
    ChessPiece removedPiece;
    Square removedPieceLocation;
};

struct MoveSet
{
    Move* moves;
    int count;
};
