#include <vector>
#include "../../types/Move.hpp"
#include "KnightMovesTest.hpp"
#include "../MoveFinder.hpp"


void KnightMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("KnightMovesTest");

    EmptyBoardEveryMoveTest(test);
    KnightCanNotMoveOffTheBoard(test);
    KnightCanNotMoveToSquareWithPieceOfSameColor(test);
    KnightCanCaptureOpposingPiece(test);
}

void KnightMovesTest::EmptyBoardEveryMoveTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece knight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, false, false);
    ChessPiece knightHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, true, false);
    board[2][2] = knight;
    Square knightSquare = { 2, 2 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 8, "A knight with every move available has 8 moves");
    Move move = {
        knightSquare,
        { 4, 3 },
        knight,
        knightHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
        { 4, 3 }
    };
    test->assert_true(moves->at(0) == move, "A knight with every move available has 8 moves: 1");
    Square targetSquare = { 4, 1 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(1) == move, "A knight with every move available has 8 moves: 2");

    targetSquare = { 3, 4 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(2) == move, "A knight with every move available has 8 moves: 3");

    targetSquare = { 1, 4 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(3) == move, "A knight with every move available has 8 moves: 4");

    targetSquare = { 0, 3 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(4) == move, "A knight with every move available has 8 moves: 5");

    targetSquare = { 0, 1 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(5) == move, "A knight with every move available has 8 moves: 6");

    targetSquare = { 3, 0 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(6) == move, "A knight with every move available has 8 moves: 7");

    targetSquare = { 1, 0 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(7) == move, "A knight with every move available has 8 moves: 8");

}

void KnightMovesTest::KnightCanNotMoveOffTheBoard(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece knight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, false, false);
    ChessPiece knightHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, true, false);
    board[0][0] = knight;
    Square knightSquare = { 0, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 2, "A knight cannot move off the board");

    Move move = {
        knightSquare,
        { 2, 1 },
        knight,
        knightHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
        { 2, 1}
    };
    test->assert_true(moves->at(0) == move, "A knight cannot move off the board: 1");
    Square targetSquare = { 1, 2 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    test->assert_true(moves->at(1) == move, "A knight cannot move off the board: 2");
}

void KnightMovesTest::KnightCanNotMoveToSquareWithPieceOfSameColor(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece blackKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, true, false, false);
    ChessPiece blackKnightHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, true, true, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, true, false, false);
    board[0][0] = blackKnight;
    board[1][2] = blackPawn;
    Square knightSquare = { 0, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 1, "A knight cannot move to a piece of the same type");

    Move move = {
        knightSquare,
        { 2, 1 },
        blackKnight,
        blackKnightHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
        { 2, 1 }
    };

    test->assert_true(moves->at(0) == move, "A knight cannot move to a piece of the same type: 1");
}

void KnightMovesTest::KnightCanCaptureOpposingPiece(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, false, false);
    ChessPiece whiteKnightHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, true, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, true, false, false);
    board[0][0] = whiteKnight;
    board [1][2] = blackPawn;
    Square knightSquare = { 0, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 2, "A knight can capture an opposing piece");

    Move move = {
        knightSquare,
        { 2, 1 },
        whiteKnight,
        whiteKnightHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
        { 2, 1 }
    };
    test->assert_true(moves->at(0) == move, "A knight can capture an opposing piece: 1");
    Square targetSquare = { 1, 2 };
    move.end = targetSquare;
    move.removedPieceSquare = targetSquare;
    move.removedPiece = blackPawn;
    test->assert_true(moves->at(1) == move, "A knight can capture an opposing piece: 2");
}
