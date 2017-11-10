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
    board[2][2] = knight;
    Square knightSquare = { 2, 2 };
    std::unique_ptr<std::vector<Move>> moves = MoveFinder::FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 8, "A knight with every move available has 8 moves");
    Move move = {
        knightSquare,
        { 4, 3 },
        knight,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };
    test->assert_true(moves->at(0) == move, "A knight with every move available has 8 moves: 1");
    move.end.row = 4;
    move.end.column = 1;
    test->assert_true(moves->at(1) == move, "A knight with every move available has 8 moves: 2");

    move.end.row = 3;
    move.end.column = 4;
    test->assert_true(moves->at(2) == move, "A knight with every move available has 8 moves: 3");

    move.end.row = 1;
    move.end.column = 4;
    test->assert_true(moves->at(3) == move, "A knight with every move available has 8 moves: 4");

    move.end.row = 0;
    move.end.column = 3;
    test->assert_true(moves->at(4) == move, "A knight with every move available has 8 moves: 5");

    move.end.row = 0;
    move.end.column = 1;
    test->assert_true(moves->at(5) == move, "A knight with every move available has 8 moves: 6");

    move.end.row = 3;
    move.end.column = 0;
    test->assert_true(moves->at(6) == move, "A knight with every move available has 8 moves: 7");

    move.end.row = 1;
    move.end.column = 0;
    test->assert_true(moves->at(7) == move, "A knight with every move available has 8 moves: 8");

}

void KnightMovesTest::KnightCanNotMoveOffTheBoard(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece knight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, false, false);
    board[0][0] = knight;
    Square knightSquare = { 0, 0 };
    std::unique_ptr<std::vector<Move>> moves = MoveFinder::FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 2, "A knight cannot move off the board");

    Move move = {
        knightSquare,
        { 2, 1 },
        knight,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };
    test->assert_true(moves->at(0) == move, "A knight cannot move off the board: 1");
    move.end.row = 1;
    move.end.column = 2;
    test->assert_true(moves->at(1) == move, "A knight cannot move off the board: 2");
}

void KnightMovesTest::KnightCanNotMoveToSquareWithPieceOfSameColor(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece blackKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, true, false, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, true, false, false);
    board[0][0] = blackKnight;
    board[1][2] = blackPawn;
    Square knightSquare = { 0, 0 };
    std::unique_ptr<std::vector<Move>> moves = MoveFinder::FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 1, "A knight cannot move to a piece of the same type");

    Move move = {
        knightSquare,
        { 2, 1 },
        blackKnight,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };

    test->assert_true(moves->at(0) == move, "A knight cannot move to a piece of the same type: 1");
}

void KnightMovesTest::KnightCanCaptureOpposingPiece(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Knight, false, false, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceType::Pawn, true, false, false);
    board[0][0] = whiteKnight;
    board [1][2] = blackPawn;
    Square knightSquare = { 0, 0 };
    std::unique_ptr<std::vector<Move>> moves = MoveFinder::FindMoves(board, knightSquare);
    test->assert_true(moves->size() == 2, "A knight can capture an opposing piece");

    Move move = {
        knightSquare,
        { 2, 1 },
        whiteKnight,
        ChessPieceHelpers::MakeChessPiece(ChessPieceType::EmptySquare, false, false, false),
    };
    test->assert_true(moves->at(0) == move, "A knight can capture an opposing piece: 1");
    move.end.row = 1;
    move.end.column = 2;
    move.removedPiece = blackPawn;
    test->assert_true(moves->at(1) == move, "A knight can capture an opposing piece: 2");
}
