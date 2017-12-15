#pragma once
#include "IMoveFinder.hpp"
#include "SlideMoveFinder.hpp"
#include "SquareUnderAttackDeterminer.hpp"

class KingMoveFinder : public ITypedMoveFinder
{
public:
    KingMoveFinder();
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
    ChessPieceType GetPieceType() override;
private:
    void FindCastlingMoves(ChessBoard board, Square kingSquare, std::vector<Move>* moves);
    bool NoSquareBetweenKingAndCastleIsUnderAttack(ChessBoard board, std::vector<Square>& squaresBetweenKingAndCastle, bool isOpponentBlack);

    std::unique_ptr<IMoveFinder> m_straightSlideMoveFinder;
    std::unique_ptr<IMoveFinder> m_diagonalSlideMoveFinder;
    std::unique_ptr<SquareUnderAttackDeterminer> m_squareUnderAttackDeterminer;
};
