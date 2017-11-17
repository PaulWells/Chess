#include <iostream>
#include "ChessBoardTest.hpp"
#include "../ChessBoard.hpp"
#include "../ChessPiece.hpp"
#include "../../util/TerminalColor.hpp"

void ChessBoardTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("ChessBoardTest");

    ClearBoardTest(test);
    PieceAtTest(test);
    OnBoardTest(test);
    SquareEqualityTest(test);
    SquarePlusVectorTest(test);
}

void ChessBoardTest::ClearBoardTest(std::shared_ptr<Test> test)
{
    ChessBoard board;
    board[0][0] = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, false, false, false);
    ChessBoardHelpers::ClearBoard(board);
    test->assert_true(board[0][0] == ChessPieceType::EmptySquare, "Clearing the board clears the board");
}

void ChessBoardTest::PieceAtTest(std::shared_ptr<Test> test)
{
    ChessBoard board;
    ChessPiece bishop = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Bishop, true, false, false);
    board[1][1] = bishop;
    Square square = { 1, 1 };
    test->assert_true(ChessBoardHelpers::PieceAt(board, square) == bishop, "PieceAt returns the correct piece");
}

void ChessBoardTest::OnBoardTest(std::shared_ptr<Test> test)
{
    test->assert_false(ChessBoardHelpers::OnBoard({ 0, 0 }, { -1, 0 }), "Moving to row -1 is off the board");
    test->assert_true(ChessBoardHelpers::OnBoard({ 1, 0 }, { -1, 0 }), "Moving to row 0 is on the board");
    test->assert_true(ChessBoardHelpers::OnBoard({ 7, 0 }, { -1, 0 }), "Moving to row 6 is on the board");
    test->assert_true(ChessBoardHelpers::OnBoard({ 7, 0 }, { 0, 0 }), "Staying on row 7 is on the board");
    test->assert_false(ChessBoardHelpers::OnBoard({ 7, 0 }, { 1, 0 }), "Moving to row 8 is off the board");
    test->assert_true(ChessBoardHelpers::OnBoard({ 0, 7 }, { 0, 0 }), "Staying on column 7 is on the board");
    test->assert_false(ChessBoardHelpers::OnBoard({ 0, 7 }, { 0, 1 }), "Moving to column 8 is off the board");
    test->assert_false(ChessBoardHelpers::OnBoard({ 0, 7 }, { 0, 2 }), "Moving to column 9 is off the board");
    test->assert_false(ChessBoardHelpers::OnBoard({ 9, 10 }, { 0, 0 }), "Moving to row 9 and column 10 is off the board");
    test->assert_false(ChessBoardHelpers::OnBoard({ 0, 0 }, { 0, -1 }), "Moving to column -1 is off the board");
}

void ChessBoardTest::SquareEqualityTest(std::shared_ptr<Test> test)
{
    Square square2 = { 3, 4 };
    Square square = { 3, 4 };
    test->assert_true(square == square2, "Squares at the same position are equal");
    square = { 4, 3 };
    test->assert_false(square == square2, "Squares at different positions are not equal");
}

void ChessBoardTest::SquarePlusVectorTest(std::shared_ptr<Test> test)
{
    Square square = { 1, 2 };
    Vector vector = { 1, -1 };
    Square resultSquare = { 2, 1 };
    test->assert_true(square + vector == resultSquare, "Square and Vector addition returns the correct square");
}
