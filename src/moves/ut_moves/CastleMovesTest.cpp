#include <vector>
#include "../../types/Move.hpp"
#include "CastleMovesTest.hpp"
#include "../MoveFinder.hpp"


void CastleMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("CastleMovesTest");

    CanNotMoveOffBoardTest(test);
    CanNotMovePastFriendlyPieceTest(test);
    CanCaptureOpposingPieceTest(test);
}

static bool ContainsMoveWithSameEndPosition(std::vector<Move>* moves, Move move)
{
    for (int i = 0; i < moves->size(); i++)
    {
        if (moves->at(i).end == move.end)
        {
            return true;
        }
    }
    return false;
}

void CastleMovesTest::CanNotMoveOffBoardTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Castle, false, false, false);
    board[2][2] = whiteCastle;

    Square castleSquare = { 2, 2 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, castleSquare);
    test->assert_true(moves->size() == 14, "A Castle will move until it reaches the end of the board");
    Move move = {
        castleSquare,
        { 0, 2 },
        whiteCastle,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 1");

    move.end.row = 1;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 2");
    move.end.row = 3;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 4");
    move.end.row = 4;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 5");
    move.end.row = 5;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 6");
    move.end.row = 6;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 7");
    move.end.row = 7;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 8");
    move.end.row = 2;
    move.end.column = 0;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 9");
    move.end.column = 1;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 10");
    move.end.column = 3;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 12");
    move.end.column = 4;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 13");
    move.end.column = 5;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 14");
    move.end.column = 6;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 15");
    move.end.column = 7;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 16");
}

void CastleMovesTest::CanNotMovePastFriendlyPieceTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Castle, false, false, false);
    board[0][0] = whiteCastle;
    Square castleSquare = { 0, 0 };

    ChessPiece whitePawn = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, false, false, false);
    board[0][3] = whitePawn;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, castleSquare);
    test->assert_true(moves->size() == 9, "A Castle can not move past a friendly chess piece");
    Move move = {
        castleSquare,
        { 0, 1 },
        whiteCastle,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 1");

    move.end.column = 2;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can not move off board: 2");

    move.end.column = 3;
    test->assert_false(ContainsMoveWithSameEndPosition(moves.get(), move), "Castle can not move to square occupied by a friendly piece");
    move.end.column = 4;
    test->assert_false(ContainsMoveWithSameEndPosition(moves.get(), move), "Castle can not move to a square on the other side of a friendly piece");

}

void CastleMovesTest::CanCaptureOpposingPieceTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Castle, false, false, false);
    board[0][0] = whiteCastle;
    Square castleSquare = { 0, 0 };

    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, true, false, false);
    board[0][3] = blackPawn;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, castleSquare);
    test->assert_true(moves->size() == 10, "A Castle can capture an opposing piece");

    Move move = {
        castleSquare,
        { 0, 3 },
        whiteCastle,
        blackPawn
    };

    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Castle can move to square occupied by an opposing piece");
    move.end.column = 4;
    move.removedPiece = ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false);
    test->assert_false(ContainsMoveWithSameEndPosition(moves.get(), move), "Castle can not move to a square on the other side of an opposing piece");
}
