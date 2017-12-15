#include <iostream>
#include "MoveHelpersTest.hpp"
#include "../ChessBoard.hpp"
#include "../ChessPiece.hpp"
#include "../Move.hpp"
#include "../../util/TerminalColor.hpp"

void MoveHelpersTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("MoveHelpersTest");

    CopyMoveWithPromotionTest(test);
}

void MoveHelpersTest::CopyMoveWithPromotionTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece pawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    board[0][0] = pawn;
    Square square = { 0, 0 };
    Vector vector = { 1, 1 };
    Move move = MoveHelpers::CreateMove(board, square, vector);

    Move copyMove = MoveHelpers::CopyMoveWithPromotion(move, ChessPieceTypes::Knight);

    ChessPiece endState = copyMove.endState;
    uint8_t endStateType = ChessPieceHelpers::GetPieceType(endState);
    test->assert_true(endStateType == ChessPieceTypes::Knight, "CopyMoveWithPromotion changes piece type of endState");

    copyMove.endState = move.endState;
    test->assert_true(copyMove == move, "CopyMoveWithPromotion does not change the rest of the move");
}
