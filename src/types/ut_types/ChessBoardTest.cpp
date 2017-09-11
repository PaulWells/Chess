#include <iostream>
#include "ChessBoardTest.hpp"
#include "../ChessBoard.hpp"
#include "../ChessPiece.hpp"

void ChessBoardTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("ChessBoardTest");

    ChessBoard board;
    board[0][0] = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, false, false, false);
    ChessBoardHelpers::ClearBoard(board);
    test->assert_true(board[0][0] == ChessPieceType::EmptySquare, "Clearing the board clears the board");

    ChessPiece bishop = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Bishop, true, false, false);
    board[1][1] = bishop;
    Square square = { 1, 1 };
    test->assert_true(ChessBoardHelpers::PieceAt(board, square) == bishop, "PieceAt returns the correct piece");

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

    Square square2 = { 3, 4 };
    square = { 3, 4 };
    test->assert_true(square == square2, "Squares at the same position are equal");
    square = { 4, 3 };
    test->assert_false(square == square2, "Squares at different positions are not equal");

    square = { 2, 1 };
    test->assert_true(ChessBoardHelpers::GetTargetSquare({ 1, 2 }, { 1, -1 }) == square, "GetTargetSquare returns the correct square");
}
