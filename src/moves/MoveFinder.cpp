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
#include "CastleMoveFinder.hpp"

MoveFinder::MoveFinder()
{
    m_knightMoveFinder = std::make_unique<KnightMoveFinder>();
    m_castleMoveFinder = std::make_unique<CastleMoveFinder>();
}

// The square represents the piece to find moves for.
std::unique_ptr<std::vector<Move>> MoveFinder::FindMoves(ChessBoard board, Square square)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    std::unique_ptr<std::vector<Move>> moves;

    switch (ChessPieceHelpers::GetPieceType(piece))
    {
        case ChessPieceType::EmptySquare:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        case ChessPieceType::Pawn:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        case ChessPieceType::Bishop:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        case ChessPieceType::Knight:
            moves = m_knightMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::Castle:
            moves = m_castleMoveFinder->FindMoves(board, square);
        break;
        case ChessPieceType::Queen:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        case ChessPieceType::King:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
        break;
        default:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
            std::cerr << "MoveFinder::FindMoves switch (ChessPieceHelpers::GetPieceType(piece)) default should not be hit" << std::endl;
    }
    return moves;
}
