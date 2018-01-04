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
#include "QueenMoveFinder.hpp"
#include "PawnMoveFinder.hpp"
#include "KingMoveFinder.hpp"
#include "CastleMoveFinder.hpp"
#include "BishopMoveFinder.hpp"
#include "../util/FailFast.hpp"

MoveFinder::MoveFinder()
{
    m_knightMoveFinder = std::make_unique<KnightMoveFinder>();
    m_castleMoveFinder = std::make_unique<CastleMoveFinder>();
    m_bishopMoveFinder = std::make_unique<BishopMoveFinder>();
    m_queenMoveFinder = std::make_unique<QueenMoveFinder>();
    m_pawnMoveFinder = std::make_unique<PawnMoveFinder>();
    m_kingMoveFinder = std::make_unique<KingMoveFinder>();
}

std::unique_ptr<std::vector<Move>> MoveFinder::FindMoves(ChessBoard board, bool forBlack)
{
    std::unique_ptr<std::vector<Move>> moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
    for (int column = 0; column < BOARD_WIDTH; column++)
    {
        for (int row = 0; row < BOARD_WIDTH; row++)
        {
            Square square = { row, column };
            ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
            bool pieceIsBlack = ChessPieceHelpers::IsBlack(piece);
            if (pieceIsBlack == forBlack)
            {
                // TODO: filter moves that put king in check.
                std::unique_ptr<std::vector<Move>> newMoves = FindMoves(board, square);
                moves->insert(moves->end(), newMoves->begin(), newMoves->end());
            }
        }
    }
    return moves;
}

// The square represents the piece to find moves for.
std::unique_ptr<std::vector<Move>> MoveFinder::FindMoves(ChessBoard board, Square square)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    std::unique_ptr<std::vector<Move>> moves;

    switch (ChessPieceHelpers::GetPieceType(piece))
    {
        case ChessPieceTypes::EmptySquare:
            // An empty square has no moves.
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        case ChessPieceTypes::Pawn:
            moves = m_pawnMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceTypes::Bishop:
            moves = m_bishopMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceTypes::Knight:
            moves = m_knightMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceTypes::Castle:
            moves = m_castleMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceTypes::Queen:
            moves = m_queenMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceTypes::King:
            moves = m_kingMoveFinder->FindMoves(board, square);
        break;
        default:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
            FAIL_FAST("MoveFinder::FindMoves switch (ChessPieceHelpers::GetPieceType(piece)) default should not be hit");
    }
    return moves;
}
