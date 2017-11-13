#include <vector>
#include "../../types/Move.hpp"
#include "BishopMovesTest.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"


void BishopMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("BishopMovesTest");

    BishopMovesDiagonallyTest(test);
}

void BishopMovesTest::BishopMovesDiagonallyTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteBishop = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Bishop, false, false, false);
    board[2][2] = whiteBishop;

    Square bishopSquare = { 2, 2 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, bishopSquare);
    test->assert_true(moves->size() == 11, "A bishop moves diagonally");
    Move move = {
        bishopSquare,
        { 3, 3 },
        whiteBishop,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 1");
    move.end.row = 3;
    move.end.column = 1;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 2");
    move.end.row = 1;
    move.end.column = 3;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 3");
    move.end.row = 1;
    move.end.column = 1;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 4");

    move.end.row = 2;
    move.end.column = 1;
    test->assert_false(MoveTestHelpers::ContainsMoveWithSameEndPosition(moves.get(), move), "Bishop does not move straight");
}
