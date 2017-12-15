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
    ChessPiece whiteBishop = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, false, false, false);
    ChessPiece whiteBishopHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, false, true, false);
    board[2][2] = whiteBishop;

    Square bishopSquare = { 2, 2 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, bishopSquare);
    test->assert_true(moves->size() == 11, "A bishop moves diagonally");
    Move move = {
        bishopSquare,
        { 3, 3 },
        whiteBishop,
        whiteBishopHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 3, 3 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 1");
    Square endSquare = { 3, 1 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 2");
    endSquare = { 1, 3 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 3");
    endSquare = { 1, 1 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Bishop moves diagonally: 4");

    endSquare = { 2, 1 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_false(MoveTestHelpers::ContainsMoveWithSameEndPosition(moves.get(), move), "Bishop does not move straight");
}
