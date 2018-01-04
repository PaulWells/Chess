#include <vector>
#include "../../types/Move.hpp"
#include "MoveFinderTest.hpp"
#include "../MoveFinder.hpp"

void MoveFinderTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("MoveFinderTest");

    EmptySquaresHaveNoMoves(test);
    FindsMovesForAllPiecesOfCorrectColor(test);
}

void MoveFinderTest::EmptySquaresHaveNoMoves(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    board[0][0] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);
    Square emptySquare = { 0, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, emptySquare);
    test->assert_true(moves->size() == 0, "Empty squares do not have any moves");
}

void MoveFinderTest::FindsMovesForAllPiecesOfCorrectColor(std::shared_ptr<Test> test)
{

    ChessBoard board = { 0 };
    ChessPiece whiteKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, false, false, false);
    ChessPiece blackKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, true, false, false);
    board[0][0] = whiteKnight;
    board[7][7] = whiteKnight;
    board[0][7] = blackKnight;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, false /*forBlack*/);

    test->assert_true(moves->size() == 4, "Only moves for white pieces are found");
}
