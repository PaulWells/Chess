#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/ChessPiece.hpp"
#include "../types/Move.hpp"
#include "PawnMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

static bool SquareIsEmpty(ChessBoard board, Square square)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    return (ChessPieceHelpers::GetPieceType(piece) == ChessPieceType::EmptySquare);
}

static bool SquareContainsOpposingPiece(ChessBoard board, Square square, ChessPiece movingChessPiece)
{
    ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
    return !(ChessPieceHelpers::GetPieceType(piece) == ChessPieceType::EmptySquare) &&
           !ChessPieceHelpers::PiecesAreSameColor(movingChessPiece, piece);
}

static void AddDoubleForwardMoveIfValid(
    ChessBoard board,
    Square startSquare,
    Vector moveForwardVector,
    std::vector<Move>* moves)
{
    Square intermediateSquare = startSquare + moveForwardVector;
    Vector moveForwardTwoVector = moveForwardVector * 2;
    Square targetSquare = startSquare + moveForwardTwoVector;
    if (SquareIsEmpty(board, targetSquare) && SquareIsEmpty(board, intermediateSquare))
    {
        Move move = MoveHelpers::CreateMove(board, startSquare, moveForwardTwoVector);
        move.endState = ChessPieceHelpers::MarkPawnAsMovedTwoSpaces(move.startState);
        moves->push_back(move);
    }
}

static void AddForwardMoveIfValid(
    ChessBoard board,
    Square startSquare,
    Vector moveForwardVector,
    std::vector<Move>* moves)
{
    Square targetSquare = startSquare + moveForwardVector;
    if (SquareIsEmpty(board, targetSquare))
    {
        Move move = MoveHelpers::CreateMove(board, startSquare, moveForwardVector);
        move.endState = ChessPieceHelpers::ClearMovedTwoSpaces(move.startState);
        moves->push_back(move);
    }
}

static void AddAttackMoveIfValid(
    ChessBoard board,
    Square startSquare,
    ChessPiece movingPiece,
    Vector attackVector,
    std::vector<Move>* moves)
{
    Square targetSquare = startSquare + attackVector;
    if (SquareContainsOpposingPiece(board, targetSquare, movingPiece))
    {
        Move move = MoveHelpers::CreateMove(board, startSquare, attackVector);
        move.endState = ChessPieceHelpers::ClearMovedTwoSpaces(move.startState);
        moves->push_back(move);
    }
}

static bool SquareContainsOpposingPawnThatJustDoubleJumped(
    ChessBoard board,
    Square square,
    ChessPiece piece)
{
    if (SquareContainsOpposingPiece(board, square, piece))
    {
        ChessPiece targetPiece = ChessBoardHelpers::PieceAt(board, square);
        return (ChessPieceHelpers::IsPawn(targetPiece) &&
               ChessPieceHelpers::JustMovedTwoSpaces(targetPiece));
    }
    return false;
}

static void AddEnPassantAttackMoveIfValid(
    ChessBoard board,
    Square startSquare,
    ChessPiece movingPiece,
    Vector sideVector,
    std::vector<Move>* moves)
{
    Square enPassantTarget = startSquare + sideVector;
    if (SquareContainsOpposingPawnThatJustDoubleJumped(board, enPassantTarget, movingPiece))
    {
        Move move = MoveHelpers::CreateMove(board, startSquare, sideVector);
        // CreateMove defaults to the removed piece being located where the movingPiece
        // moves to.  Override these defaults.
        move.removedPiece = ChessBoardHelpers::PieceAt(board, enPassantTarget);
        move.removedPieceSquare = enPassantTarget;
        moves->push_back(move);
    }
}

static void AddAttackMovesIfValid(
    ChessBoard board,
    Square startSquare,
    ChessPiece movingPiece,
    Vector moveForwardVector,
    std::vector<Move>* moves)
{
    Vector sideVector1 = { 0,  1 };
    Vector sideVector2 = { 0, -1 };
    Vector attackVector1 = moveForwardVector + sideVector1;
    Vector attackVector2 = moveForwardVector + sideVector2;

    AddAttackMoveIfValid(board, startSquare, movingPiece, attackVector1, moves);
    AddAttackMoveIfValid(board, startSquare, movingPiece, attackVector2, moves);
    AddEnPassantAttackMoveIfValid(board, startSquare, movingPiece, sideVector1, moves);
    AddEnPassantAttackMoveIfValid(board, startSquare, movingPiece, sideVector2, moves);
}

std::unique_ptr<std::vector<Move>> PawnMoveFinder::FindMoves(ChessBoard board, Square startSquare)
{
    std::unique_ptr<std::vector<Move>> moves = std::make_unique<std::vector<Move>>(std::vector<Move>());
    ChessPiece pawn = ChessBoardHelpers::PieceAt(board, startSquare);

    bool isPawnBlack = ChessPieceHelpers::IsBlack(pawn);
    Vector upVector = { -1, 0 };
    Vector downVector = { 1, 0 };
    Vector moveForwardVector = (isPawnBlack ? downVector : upVector);
    AddForwardMoveIfValid(board, startSquare, moveForwardVector, moves.get());

    bool pawnHasNotMoved = !ChessPieceHelpers::HasMoved(pawn);
    if (pawnHasNotMoved)
    {
        AddDoubleForwardMoveIfValid(board, startSquare, moveForwardVector, moves.get());
    }

    AddAttackMovesIfValid(board, startSquare, pawn, moveForwardVector, moves.get());

    return std::move(moves);
}
