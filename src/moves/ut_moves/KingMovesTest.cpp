#include <vector>
#include "../../types/Move.hpp"
#include "KingMovesTest.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"


void KingMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("KingMovesTest");

    KingCanOnlyMoveOneSquare(test);
    WhiteCastlingMoveToTheRightTest(test);
}

void KingMovesTest::WhiteCastlingMoveToTheRightTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, false, false, false);
    ChessPiece whiteCastleHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, false, true, false);
    ChessPiece whiteKing = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, false, false, false);
    ChessPiece whiteKingHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, false, true, false);
    board[7][7] = whiteCastle;
    board[7][4] = whiteKing;

    Square castleSquare = { 7, 7 };
    Square kingStartSquare = { 7, 4 };
    Square kingEndSquare = { 7, 6 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, kingStartSquare);

    test->assert_true(moves->size() == 6, "A King can castle");
    Move move = {
        kingStartSquare,
        kingEndSquare,
        whiteKing,
        whiteKingHasMoved,
        whiteCastle,
        castleSquare
    };
    test->assert_true(std::find(moves->begin(), moves->end(), move) != moves->end(), "A king can castle: 2");

    ChessPiece whitePawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    board[7][6] = whitePawn;
    moves = moveFinder->FindMoves(board, kingStartSquare);
    test->assert_true(moves->size() == 5, "A King cannot castle if there is a piece in the way");
    board[7][6] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);

    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    board[6][6] = blackPawn;
    moves = moveFinder->FindMoves(board, kingStartSquare);
    test->assert_true(moves->size() == 5, "A King cannot castle if an opposing piece is attacking a square between the king and castle");
    board[6][6] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);

    board[6][3] = blackPawn;
    moves = moveFinder->FindMoves(board, kingStartSquare);
    test->assert_true(moves->size() == 5, "A King cannot castle if it is in check");
    board[6][3] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);

}


void KingMovesTest::KingCanOnlyMoveOneSquare(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whiteKingHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, false, true, false);
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
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
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
