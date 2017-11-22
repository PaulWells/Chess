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

static const int UNLIMITED_RANGE = 8;

class SlideMoveFinder : public IMoveFinder
{
public:
    static IMoveFinder* CreateSlideMoveFinder(SlideMoveType type, int rangeLimit = UNLIMITED_RANGE);
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
private:
    SlideMoveFinder(Vector[NUMBER_SLIDE_DIRECTIONS], int rangeLimit);
    SlideMoveFinder();
    Vector m_slideDirections[NUMBER_SLIDE_DIRECTIONS];

    int m_rangeLimit; // The maximum number of squares a piece can move.
                      // -1 means there is no maximum.
                      // Only King pieces set a positive value (1).
};
