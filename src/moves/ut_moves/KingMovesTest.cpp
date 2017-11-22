#include <vector>
#include "../../types/Move.hpp"
#include "KingMovesTest.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"


void KingMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("KingMovesTest");

    KingCanOnlyMoveOneSquare(test);
}

void KingMovesTest::KingCanOnlyMoveOneSquare(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteKingHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceType::King, false, true, false);
    board[0][0] = whiteKingHasMoved;

    Square kingSquare = { 0, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, kingSquare);
    test->assert_true(moves->size() == 3, "A king moves one square in any direction");

    Move move = {
        kingSquare,
        { 0, 1 },
        whiteKingHasMoved,
        whiteKingHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
        { 0, 1 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "King moves straight: 1");

    Square endSquare = { 1, 0 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "King moves straight: 2");

    endSquare = { 1, 1 };
    move.end = endSquare;
    move.removedPieceSquare = endSquare;
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "King moves diagonally");
}
