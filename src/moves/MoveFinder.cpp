#include <iostream>
#include <vector>
#include <memory>
#include "../types/ChessBoard.hpp"
#include "../types/ChessPiece.hpp"
#include "../types/Move.hpp"
#include "IMoveFinder.hpp"
#include "MoveFinder.hpp"
#include "MoveFinderHelpers.hpp"
#include "KnightMoveFinder.hpp"
#include "SlideMoveFinder.hpp"
#include "QueenMoveFinder.hpp"
#include "PawnMoveFinder.hpp"
#include "KingMoveFinder.hpp"
#include "../util/FailFast.hpp"

MoveFinder::MoveFinder()
{
    m_knightMoveFinder = std::make_unique<KnightMoveFinder>();
    m_castleMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Straight));
    m_bishopMoveFinder = std::unique_ptr<IMoveFinder>(SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Diagonal));
    m_queenMoveFinder = std::make_unique<QueenMoveFinder>();
    m_pawnMoveFinder = std::make_unique<PawnMoveFinder>();
    m_kingMoveFinder = std::make_unique<KingMoveFinder>();
}

// The square represents the piece to find moves for.
std::unique_ptr<std::vector<Move>> MoveFinder::FindMoves(ChessBoard board, Square square)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    std::unique_ptr<std::vector<Move>> moves;

    switch (ChessPieceHelpers::GetPieceType(piece))
    {
        case ChessPieceType::EmptySquare:
            // An empty square has no moves.
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        case ChessPieceType::Pawn:
            moves = m_pawnMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::Bishop:
            moves = m_bishopMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::Knight:
            moves = m_knightMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::Castle:
            moves = m_castleMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::Queen:
            moves = m_queenMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::King:
            moves = m_kingMoveFinder->FindMoves(board, square);
        break;
        default:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
            FAIL_FAST("MoveFinder::FindMoves switch (ChessPieceHelpers::GetPieceType(piece)) default should not be hit");
    }
    return moves;
}
