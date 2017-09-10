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
}
