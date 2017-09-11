#include <iostream>
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
MoveSet MoveFinder::FindMoves(ChessBoard board, Square square)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    MoveSet moveSet;

    switch (ChessPieceHelpers::GetPieceType(piece))
    {
        case ChessPieceType::EmptySquare:
            moveSet = { nullptr, 0 };
        break;
        case ChessPieceType::Pawn:
            moveSet = { nullptr, 0 };
        break;
        case ChessPieceType::Bishop:
            moveSet = { nullptr, 0 };
        break;
        case ChessPieceType::Knight:
            moveSet = GetKnightMoveSet(board, square);
        break;
        case ChessPieceType::Castle:
            moveSet = { nullptr, 0 };
        break;
        case ChessPieceType::Queen:
            moveSet = { nullptr, 0 };
        break;
        case ChessPieceType::King:
            moveSet = { nullptr, 0 };
        break;
        default:
            moveSet = { nullptr, 0 };
            std::cerr << "MoveFinder::FindMoves switch (ChessPieceHelpers::GetPieceType(piece)) default should not be hit" << std::endl;
    }
    return moveSet;
}

MoveSet MoveFinder::GetKnightMoveSet(ChessBoard board, Square square)
{
    int moveCount = 0;
    Move moves[MAX_KNIGHT_MOVES];
    for (int i = 0; i < MAX_KNIGHT_MOVES; i++ )
    {
        if (ValidateKnightMove(board, square, knightDistances[i]))
        {
            Move move = CreateKnightMove(board, square, knightDistances[i]);
            moves[moveCount] = move;
            moveCount++;
        }
    }
    return { moves, moveCount };
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
