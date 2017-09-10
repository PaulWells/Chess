#include "MoveFinderTest.hpp"
#include "../MoveFinder.hpp"

void MoveFinderTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("MoveFinderTest");

    ChessBoard board;
    board[0][0] = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, false, false, false);
    ChessBoardHelpers::ClearBoard(board);
    Square emptySquare = { 0, 0 };
    MoveSet moveSet = MoveFinder::FindMoves(board, emptySquare);
    test->assert_true(moveSet.count == 0, "Empty squares do not have any moves");

}