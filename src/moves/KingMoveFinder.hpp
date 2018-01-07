#pragma once
#include "IMoveFinder.hpp"
#include "SlideMoveFinder.hpp"
#include "SquareUnderAttackDeterminer.hpp"

class KingMoveFinder : public ITypedMoveFinder
{
public:
    KingMoveFinder(bool includeCastlingMoves);
    static Square GetCastlePositionAfterCastling(Square kingEndSquare);
    std::unique_ptr<std::vector<Move>> FindMoves(ChessBoard board, Square square) override;
    ChessPieceType GetPieceType() override;
private:
    void FindCastlingMoves(ChessBoard board, Square kingSquare, std::vector<Move>* moves);
    bool NoSquareBetweenKingAndCastleIsUnderAttack(ChessBoard board, std::vector<Square>& squaresBetweenKingAndCastle, bool isOpponentBlack);
    bool KingIsInCheck(ChessBoard board, Square kingSquare, bool isOpponentBlack);

    std::unique_ptr<IMoveFinder> m_straightSlideMoveFinder;
    std::unique_ptr<IMoveFinder> m_diagonalSlideMoveFinder;
    std::unique_ptr<SquareUnderAttackDeterminer> m_squareUnderAttackDeterminer;

    // This configuration is necessary to break a circular dependency.
    // KingMoveFinder uses SquareUnderAttackDeterminer to see if it has a
    // valid castling move but SquareUnderAttackDeterminer uses a KingMoveFinder
    // to see if an opponent's king is blocking the castling move.
    bool m_includeCastlingMoves;
};
