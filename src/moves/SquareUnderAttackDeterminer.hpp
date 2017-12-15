#pragma once
#include "IMoveFinder.hpp"

class SquareUnderAttackDeterminer
{
public:
    SquareUnderAttackDeterminer();
    bool IsSquareUnderAttack(ChessBoard board, Square square, bool isOpponentBlack);
private:
    // This class will take advantage of the fact that the attack moves of every piece are symmetrical.
    // This means that if piece A can attack piece B then piece B can also attack piece A if it is the
    // same type of piece.  Instead of finding all of the moves the opponent's pieces can make and
    // seeing if any of them attack the square, pretend that there is a piece of each type on the
    // square and if it can attack a piece of the same type then the square is under attack.

    // Pawn, Knight, Bishop, Castle, Queen, King.
    std::unique_ptr<std::vector<std::unique_ptr<ITypedMoveFinder>>> m_moveFinders;
};
