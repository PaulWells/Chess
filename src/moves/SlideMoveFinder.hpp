#pragma once
#include "IMoveFinder.hpp"

enum SlideMoveType
{
    Straight,
    Diagonal
};

static const uint8_t NUMBER_SLIDE_DIRECTIONS = 4;
static Vector straightSlideDirections[NUMBER_SLIDE_DIRECTIONS] = {
    {  0,  1 },
    {  1,  0 },
    {  0, -1 },
    { -1,  0 },
};

static Vector diagonalSlideDirections[NUMBER_SLIDE_DIRECTIONS] = {
    {  1,  1 },
    {  1, -1 },
    { -1,  1 },
    { -1, -1 },
};

class SlideMoveFinder : public IMoveFinder
{
public:
    static IMoveFinder* CreateSlideMoveFinder(SlideMoveType type);
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
private:
    SlideMoveFinder(Vector[NUMBER_SLIDE_DIRECTIONS]);
    SlideMoveFinder();
    Vector m_slideDirections[NUMBER_SLIDE_DIRECTIONS];
};
