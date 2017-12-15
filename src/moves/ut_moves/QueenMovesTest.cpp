#include <vector>
#include "../../types/Move.hpp"
#include "QueenMovesTest.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"


void QueenMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("QueenMovesTest");

    QueenMovesBothStraightAndDiagonally(test);
}

void QueenMovesTest::QueenMovesBothStraightAndDiagonally(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, false, false, false);
    ChessPiece whiteQueenHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, false, true, false);
    board[2][2] = whiteQueen;

    Square queenSquare = { 2, 2 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, queenSquare);
    test->assert_true(moves->size() == 25, "A queen moves both straight and diagonally");
    Move move = {
        queenSquare,
        { 3, 3 },
        whiteQueen,
        whiteQueenHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 3, 3 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Queen moves diagonally");
    Square endSquare = { 2, 1 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "Queen moves straight");
}
