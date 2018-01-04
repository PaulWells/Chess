#include <vector>
#include "../../types/Move.hpp"
#include "SquareUnderAttackDeterminerTest.hpp"
#include "../SquareUnderAttackDeterminer.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"


void SquareUnderAttackDeterminerTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("SquareUnderAttackDeterminerTest");

    EmptyBoardTest(test);
    SquareUnderAttackDeterminerDoesNotChangeBoardState(test);
    DetectsAttackByPawn(test);
    DetectsAttackByKnight(test);
    DetectsAttackByCastle(test);
    DetectsAttackByBishop(test);
    DetectsAttackByQueen(test);
    DetectsAttackByKing(test);
    DoesNotConsiderFriendlyUnitsAsAttacking(test);
}

void SquareUnderAttackDeterminerTest::EmptyBoardTest(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square square = { 2, 2 };
    bool isOpponentBlack = false;

    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, square, isOpponentBlack);
    test->assert_false(squareIsUnderAttack, "Square on empty board is not under attack");
}

void SquareUnderAttackDeterminerTest::SquareUnderAttackDeterminerDoesNotChangeBoardState(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board1 = { 0 };
    ChessBoard board2 = { 0 };
    Square square = { 2, 2 };

    ChessPiece pawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);

    ChessBoardHelpers::SetPieceAt(board1, square, pawn);
    ChessBoardHelpers::SetPieceAt(board2, square, pawn);

    bool isOpponentBlack = true;

    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board1, square, isOpponentBlack);
    test->assert_false(squareIsUnderAttack, "Piece on empty board is not under attack");

    test->assert_true(ChessBoardHelpers::AreBoardsEqual(board1, board2), "SquareUnderAttackDeterminer does not change board state");

}

void SquareUnderAttackDeterminerTest::DetectsAttackByPawn(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square whitePawnSquare = { 3, 3 };
    Square squareUnderAttack = { 2, 2 };
    Square squareNotUnderAttack = { 2, 3 };
    ChessPiece whitePawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);

    ChessBoardHelpers::SetPieceAt(board, whitePawnSquare, whitePawn);

    bool isOpponentBlack = false;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square pawn can attack is under attack by pawn");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square pawn moves to is not under attack by pawn");
}

void SquareUnderAttackDeterminerTest::DetectsAttackByKnight(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square whiteKnightSquare = { 3, 3 };
    Square squareUnderAttack = { 5, 4 };
    Square squareNotUnderAttack = { 2, 3 };
    ChessPiece whiteKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, false, false, false);

    ChessBoardHelpers::SetPieceAt(board, whiteKnightSquare, whiteKnight);

    bool isOpponentBlack = false;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square knight can attack is under attack");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square knight cannot attack is not under attack by knight");

}

void SquareUnderAttackDeterminerTest::DetectsAttackByCastle(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square blackCastleSquare = { 3, 3 };
    Square squareUnderAttack = { 6, 3 };
    Square squareNotUnderAttack = { 4, 4 };
    ChessPiece blackCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, true, false, false);

    ChessBoardHelpers::SetPieceAt(board, blackCastleSquare, blackCastle);

    bool isOpponentBlack = true;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square castle can attack is under attack");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square castle cannot attack is not under attack");
}

void SquareUnderAttackDeterminerTest::DetectsAttackByBishop(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square blackBishopSquare = { 3, 3 };
    Square squareUnderAttack = { 6, 6 };
    Square squareNotUnderAttack = { 4, 3 };
    ChessPiece blackBishop = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, true, false, false);

    ChessBoardHelpers::SetPieceAt(board, blackBishopSquare, blackBishop);

    bool isOpponentBlack = true;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square bishop can attack is under attack");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square bishop cannot attack is not under attack");

}

void SquareUnderAttackDeterminerTest::DetectsAttackByQueen(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square blackQueenSquare = { 3, 3 };
    Square squareUnderAttack = { 6, 6 };
    Square squareNotUnderAttack = { 4, 3 };
    ChessPiece blackQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, true, false, false);

    ChessBoardHelpers::SetPieceAt(board, blackQueenSquare, blackQueen);

    bool isOpponentBlack = true;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square queen can attack is under attack");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square queen cannot attack is not under attack");

}

void SquareUnderAttackDeterminerTest::DetectsAttackByKing(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square blackKingSquare = { 3, 3 };
    Square squareUnderAttack = { 4, 4 };
    Square squareNotUnderAttack = { 5, 3 };
    ChessPiece blackKing = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, true, false, false);

    ChessBoardHelpers::SetPieceAt(board, blackKingSquare, blackKing);

    bool isOpponentBlack = true;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square king can attack is under attack");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square king cannot attack is not under attack");

}

void SquareUnderAttackDeterminerTest::DoesNotConsiderFriendlyUnitsAsAttacking(std::shared_ptr<Test> test)
{
    std::unique_ptr<SquareUnderAttackDeterminer> squareUnderAttackDeterminer = std::make_unique<SquareUnderAttackDeterminer>();

    ChessBoard board = { 0 };
    Square blackQueenSquare = { 3, 3 };
    Square squareUnderAttack = { 6, 6 };
    Square squareNotUnderAttack = { 4, 3 };
    ChessPiece blackQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, true, false, false);

    ChessBoardHelpers::SetPieceAt(board, blackQueenSquare, blackQueen);

    bool isOpponentBlack = false;
    bool squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, isOpponentBlack);
    test->assert_false(squareIsUnderAttack, "Square is not under attack if queen is of same color");

    squareIsUnderAttack = squareUnderAttackDeterminer->IsSquareUnderAttack(board, squareUnderAttack, !isOpponentBlack);
    test->assert_true(squareIsUnderAttack, "Square is under attack if queen is of different color");
}
