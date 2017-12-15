#include <vector>
#include "../../types/Move.hpp"
#include "MoveFinderTest.hpp"
#include "../MoveFinder.hpp"

void MoveFinderTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("MoveFinderTest");

    ChessBoard board = { 0 };
    board[0][0] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    Square emptySquare = { 0, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, emptySquare);
    test->assert_true(moves->size() == 0, "Empty squares do not have any moves");
}
