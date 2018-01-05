#include <vector>
#include "../../types/Move.hpp"
#include "PawnMovesTest.hpp"
#include "../MoveFinder.hpp"


void PawnMovesTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("PawnMovesTest");

    StartingPositionMoveTest(test);
    SingleForwardMoveTest(test);
    AttackTest(test);
    EnPassantAttackTest(test);
    CantMoveForwardIntoOpposingPieceTest(test);
    CantMoveIntoFriendlyPieceTest(test);
    CantAttackOffTheBoardTest(test);
    PromotionTest(test);
    PawnAttackDoesNotWrapAroundBoardTest(test);
}

void PawnMovesTest::PawnAttackDoesNotWrapAroundBoardTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawnHasNotMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    ChessPiece blackCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, true, false, false);

    board[0][7] = blackCastle;
    board[1][0] = blackPawn;

    board[2][0] = whitePawnHasNotMoved;
    Square blackCastleSquare = { 0, 0 };
    Square blackPawnSquare = { 1, 0 };
    Square whitePawnSquare = { 2, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 0, "A pawn attack does not wrap around the board");
}

void PawnMovesTest::StartingPositionMoveTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    ChessPiece blackPawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, true, false);
    ChessPiece blackPawnHasJustDoubleJumped = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, true, true);
    board[1][1] = blackPawn;
    Square blackPawnSquare = { 1, 1 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, blackPawnSquare);

    test->assert_true(moves->size() == 2, "A pawn in its starting position has two moves");

    Move moveOneForward = {
        blackPawnSquare,
        { 2, 1 },
        blackPawn,
        blackPawnHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 2, 1 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveOneForward) != moves->end(), "A pawn in its starting position can move one forward");

    Move moveTwoForward = {
        blackPawnSquare,
        { 3, 1 },
        blackPawn,
        blackPawnHasJustDoubleJumped,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 3, 1 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveTwoForward) != moves->end(), "A pawn in its starting position can move two forward");
}

void PawnMovesTest::SingleForwardMoveTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, true, false);
    board[5][1] = whitePawnHasMoved;
    Square whitePawnSquare = { 5, 1 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 1, "A pawn that has moved and has no attack targets has one move");

    Move moveOneForward = {
        whitePawnSquare,
        { 4, 1 },
        whitePawnHasMoved,
        whitePawnHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 4, 1 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveOneForward) != moves->end(), "A pawn that has moved and has no attack targets can move forward one");
}

void PawnMovesTest::AttackTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, true, false);
    ChessPiece blackPawn1 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    ChessPiece blackPawn2 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    board[5][1] = whitePawnHasMoved;
    Square whitePawnSquare = { 5, 1 };

    board[4][0] = blackPawn1;
    board[4][2] = blackPawn2;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 3, "A pawn that has moved with two attack targets has three moves");

    Move moveOneForward = {
        whitePawnSquare,
        { 4, 1 },
        whitePawnHasMoved,
        whitePawnHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 4, 1 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveOneForward) != moves->end(), "A pawn that has attack targets can move forward");

    Move attackMove1 = {
        whitePawnSquare,
        { 4, 0 },
        whitePawnHasMoved,
        whitePawnHasMoved,
        blackPawn1,
        { 4, 0 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveOneForward) != moves->end(), "A pawn can attack an opposing piece: 1");

    Move attackMove2 = {
        whitePawnSquare,
        { 4, 2},
        whitePawnHasMoved,
        whitePawnHasMoved,
        blackPawn2,
        { 4, 2 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveOneForward) != moves->end(), "A pawn can attack an opposing piece: 2");
}

void PawnMovesTest::EnPassantAttackTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, true, false);
    ChessPiece blackPawnHasJustDoubleJumped1 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, true, true);
    ChessPiece blackPawnHasJustDoubleJumped2 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, true, true);

    board[3][1] = whitePawnHasMoved;
    Square whitePawnSquare = { 3, 1 };
    board[3][0] = blackPawnHasJustDoubleJumped1;
    Square blackPawnHasJustDoubleJumpedSquare1 = { 3, 0 };
    board[3][2] = blackPawnHasJustDoubleJumped2;
    Square blackPawnHasJustDoubleJumpedSquare2 = { 3, 2 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 3, "A pawn with two enpassant targets has three moves");

    Move moveOneForward = {
        whitePawnSquare,
        { 2, 1 },
        whitePawnHasMoved,
        whitePawnHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 2, 1 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), moveOneForward) != moves->end(), "A pawn that has attack targets can move forward");

    Move enPassantAttackMove1 = {
        whitePawnSquare,
        { 2, 0 },
        whitePawnHasMoved,
        whitePawnHasMoved,
        blackPawnHasJustDoubleJumped1,
        blackPawnHasJustDoubleJumpedSquare1
    };
    test->assert_true(std::find(moves->begin(), moves->end(), enPassantAttackMove1) != moves->end(), "A pawn can enpassant attack an opposing piece: 1");

    Move enPassantAttackMove2 = {
        whitePawnSquare,
        { 2, 2 },
        whitePawnHasMoved,
        whitePawnHasMoved,
        blackPawnHasJustDoubleJumped1,
        blackPawnHasJustDoubleJumpedSquare2
    };
    test->assert_true(std::find(moves->begin(), moves->end(), enPassantAttackMove2) != moves->end(), "A pawn can enpassant attack an opposing piece: 2");
}

void PawnMovesTest::CantMoveForwardIntoOpposingPieceTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, true, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    board[5][1] = whitePawnHasMoved;
    Square whitePawnSquare = { 5, 1 };

    board[4][1] = blackPawn;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 0, "A pawn cannot move forward into an opposing piece");
}

void PawnMovesTest::CantMoveIntoFriendlyPieceTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    ChessPiece whitePawn1 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    ChessPiece whitePawn2 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    ChessPiece whitePawn3 = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    board[5][1] = whitePawn;
    Square whitePawnSquare = { 5, 1 };

    board[4][0] = whitePawn1;
    board[4][1] = whitePawn2;
    board[4][2] = whitePawn3;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 0, "A pawn cannot move into a friendly piece");
}

void PawnMovesTest::CantAttackOffTheBoardTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };
    ChessPiece whitePawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, true, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);
    board[5][0] = whitePawnHasMoved;
    Square whitePawnSquare = { 5, 0 };

    board[4][0] = blackPawn;

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 0, "A pawn cannot attack off of the board");
}

void PawnMovesTest::PromotionTest(std::shared_ptr<Test> test)
{
    ChessBoard board = { 0 };

    ChessPiece whitePawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, true, false);
    board[1][0] = whitePawnHasMoved;
    Square whitePawnSquare = { 1, 0 };

    ChessPiece whiteQueenHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, false, true, false);
    ChessPiece whiteCastleHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, false, true, false);
    ChessPiece whiteBishopHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, false, true, false);
    ChessPiece whiteKnightHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, false, true, false);

    ChessPiece blackPawnHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, true, false);
    ChessPiece blackQueenHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, true, true, false);
    board[6][0] = blackPawnHasMoved;
    Square blackPawnSquare = { 6, 0 };

    std::unique_ptr<MoveFinder> moveFinder = std::make_unique<MoveFinder>();
    std::unique_ptr<std::vector<Move>> moves = moveFinder->FindMoves(board, whitePawnSquare);

    test->assert_true(moves->size() == 4, "A pawn that moves to the end of the board is promoted");

    Move promotionMove1 = {
        whitePawnSquare,
        { 0, 0 },
        whitePawnHasMoved,
        whiteQueenHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 0, 0 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), promotionMove1) != moves->end(), "A white pawn can be promoted to a Queen");

    Move promotionMove2 = {
        whitePawnSquare,
        { 0, 0 },
        whitePawnHasMoved,
        whiteCastleHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 0, 0 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), promotionMove2) != moves->end(), "A white pawn can be promoted to a castle");

    Move promotionMove3 = {
        whitePawnSquare,
        { 0, 0 },
        whitePawnHasMoved,
        whiteBishopHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 0, 0 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), promotionMove3) != moves->end(), "A white pawn can be promoted to a bishop");

    Move promotionMove4 = {
        whitePawnSquare,
        { 0, 0 },
        whitePawnHasMoved,
        whiteKnightHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 0, 0 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), promotionMove4) != moves->end(), "A white pawn can be promoted to a knight");

    moves = moveFinder->FindMoves(board, blackPawnSquare);

    test->assert_true(moves->size() == 4, "A black pawn that moves to the end of the board is promoted");

    Move promotionMove5 = {
        blackPawnSquare,
        { 7, 0 },
        blackPawnHasMoved,
        blackQueenHasMoved,
        ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false),
        { 7, 0 }
    };
    test->assert_true(std::find(moves->begin(), moves->end(), promotionMove5) != moves->end(), "A black pawn can be promoted");
}
