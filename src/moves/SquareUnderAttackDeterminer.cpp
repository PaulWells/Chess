#include "SquareUnderAttackDeterminer.hpp"
#include "KnightMoveFinder.hpp"
#include "QueenMoveFinder.hpp"
#include "PawnMoveFinder.hpp"
#include "KingMoveFinder.hpp"
#include "CastleMoveFinder.hpp"
#include "BishopMoveFinder.hpp"

SquareUnderAttackDeterminer::SquareUnderAttackDeterminer()
{
    m_moveFinders = std::make_unique<std::vector<std::unique_ptr<ITypedMoveFinder>>>();
    m_moveFinders->push_back(std::make_unique<CastleMoveFinder>());
    m_moveFinders->push_back(std::make_unique<BishopMoveFinder>());
    m_moveFinders->push_back(std::make_unique<KnightMoveFinder>());
    m_moveFinders->push_back(std::make_unique<QueenMoveFinder>());
    m_moveFinders->push_back(std::make_unique<PawnMoveFinder>());
    m_moveFinders->push_back(std::make_unique<KingMoveFinder>());
}

bool SquareUnderAttackDeterminer::IsSquareUnderAttack(ChessBoard board, Square square, bool isOpponentBlack)
{
    // Save the current piece at square so that when we place a virtual pieces there
    // for move finding we can restore the original piece afterwards. Saved piece
    // can be an empty square (checking if it is safe to castle) or a king
    // (checking if the king is in check).
    ChessPiece savedPiece = ChessBoardHelpers::PieceAt(board, square);

    // A square is under attack if a piece placed at that square is able to
    // attack another piece of the same type.  This is only true because the attack
    // move of every piece is symmetric.  This should be more efficient  in
    // the early game than scanning the board for every opposing piece and
    // finding its moves.  The early game is more important to optimize because
    // that is when there are more possible moves.
    std::unique_ptr<std::vector<Move>> moves;
    for (int i = 0; i < m_moveFinders->size(); i++)
    {
        ITypedMoveFinder* typedMoveFinder = (m_moveFinders->at(i)).get();
        ChessPieceType moveFinderPieceType = typedMoveFinder->GetPieceType();

        // Every piece has the same attack moves regardless of whether it has
        // already moved or not.
        bool hasMoved = true;
        ChessPiece temporaryAttackPiece = ChessPieceHelpers::MakeChessPiece(moveFinderPieceType, !isOpponentBlack, hasMoved, false /*justMovedTwoSpaces*/);
        ChessBoardHelpers::SetPieceAt(board, square, temporaryAttackPiece);

        moves = typedMoveFinder->FindMoves(board, square);

        for (int j = 0; j < moves->size(); j++)
        {
            Move move = moves->at(j);
            ChessPiece piece = move.removedPiece;
            if (ChessPieceHelpers::GetPieceType(piece) == moveFinderPieceType)
            {
                ChessBoardHelpers::SetPieceAt(board, square, savedPiece);
                return true;
            }
        }
    }

    ChessBoardHelpers::SetPieceAt(board, square, savedPiece);
    return false;
}
