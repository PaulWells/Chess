#include <iostream>
#include <vector>
#include <memory>
#include "MoveFinder.hpp"
#include "../types/ChessBoard.hpp"
#include "../types/ChessPiece.hpp"

static const uint8_t MAX_KNIGHT_MOVES = 8;
static Distance knightDistances[MAX_KNIGHT_MOVES] = {
    {  2,  1 },
    {  2, -1 },
    {  1,  2 },
    { -1,  2 },
    { -2,  1 },
    { -2, -1 },
    {  1, -2 },
    { -1, -2 }
};

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
            moves = GetKnightMoveSet(board, square);
        break;
        case ChessPieceType::Castle:
            moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
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

std::unique_ptr<std::vector<Move>> MoveFinder::GetKnightMoveSet(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
    moves->reserve(MAX_KNIGHT_MOVES);
    for (int i = 0; i < MAX_KNIGHT_MOVES; i++ )
    {
        if (ValidateKnightMove(board, square, knightDistances[i]))
        {
            Move move = CreateKnightMove(board, square, knightDistances[i]);
            moves->push_back(move);
        }
    }
    return std::move(moves);
}

bool MoveFinder::ValidateKnightMove(ChessBoard board, Square square, Distance distance)
{
    bool validMove = ChessBoardHelpers::OnBoard(square, distance);
    if (validMove)
    {
        Square endSquare = ChessBoardHelpers::GetTargetSquare(square, distance);
        ChessPiece targetPiece = ChessBoardHelpers::PieceAt(board, endSquare);
        ChessPiece movingPiece = ChessBoardHelpers::PieceAt(board, square);
        validMove = (!ChessPieceHelpers::SameColor(movingPiece, targetPiece) ||
                    ChessPieceHelpers::GetPieceType(targetPiece) == ChessPieceType::EmptySquare);
    }
    return validMove;
}

Move MoveFinder::CreateKnightMove(ChessBoard board, Square square, Distance distance)
{
    Move move;
    move.start = square;
    move.end = ChessBoardHelpers::GetTargetSquare(square, distance);
    move.startState = ChessBoardHelpers::PieceAt(board, square);
    move.removedPiece = ChessBoardHelpers::PieceAt(board, move.end);
    return move;
}
