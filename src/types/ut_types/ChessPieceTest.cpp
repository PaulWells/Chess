
#include "../ChessPiece.hpp"
#include "ChessPieceTest.hpp"
#include <iostream>

void ChessPieceTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("ChessPieceTest");

    const ChessPiece emptySquare = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);
    const ChessPiece pawnNotJustMovedTwoSpaces = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    const ChessPiece pawnJustMovedTwoSpaces = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, true);
    const ChessPiece whiteKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, false, false, false);
    const ChessPiece blackKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, true, false, false);
    const ChessPiece blackBishopHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, true, true, false);
    const ChessPiece castleHasNotMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, false, false, false);
    const ChessPiece castleHasMoved = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, false, true, false);
    const ChessPiece queen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, false, false, false);
    const ChessPiece king = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, false, false, false);

    test->assert_true(ChessPieceHelpers::IsEmptySquare(emptySquare), "emptySquare is an EmptySquare");
    test->assert_false(ChessPieceHelpers::IsPawn(emptySquare), "emptySquare is not a pawn");
    test->assert_false(ChessPieceHelpers::IsKnight(emptySquare), "emptySquare is not a knight");
    test->assert_false(ChessPieceHelpers::IsBishop(emptySquare), "emptySquare is not a bishop");
    test->assert_false(ChessPieceHelpers::IsCastle(emptySquare), "emptySquare is not a castle");
    test->assert_false(ChessPieceHelpers::IsQueen(emptySquare), "emptySquare is not a queen");
    test->assert_false(ChessPieceHelpers::IsKing(emptySquare), "emptySquare is not a king");

    test->assert_true(ChessPieceHelpers::IsPawn(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is a Pawn");
    test->assert_false(ChessPieceHelpers::IsEmptySquare(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is not a EmptySquare");
    test->assert_false(ChessPieceHelpers::IsKnight(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is not a Knight");
    test->assert_false(ChessPieceHelpers::IsBishop(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is not a Bishop");
    test->assert_false(ChessPieceHelpers::IsCastle(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is not a Castle");
    test->assert_false(ChessPieceHelpers::IsQueen(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is not a Queen");
    test->assert_false(ChessPieceHelpers::IsKing(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces is not a King");
    test->assert_false(ChessPieceHelpers::JustMovedTwoSpaces(pawnNotJustMovedTwoSpaces), "pawnNotJustMovedTwoSpaces did not just move two spaces");

    test->assert_true(ChessPieceHelpers::IsPawn(pawnJustMovedTwoSpaces), "pawnJustMovedTwoSpaces is a pawn");
    test->assert_true(ChessPieceHelpers::JustMovedTwoSpaces(pawnJustMovedTwoSpaces), "pawnJustMovedTwoSpaces just moved two spaces");

    ChessPiece pawnNoLongerJustMovedTwoSpaces = ChessPieceHelpers::ClearMovedTwoSpaces(pawnJustMovedTwoSpaces);
    test->assert_false(ChessPieceHelpers::JustMovedTwoSpaces(pawnNoLongerJustMovedTwoSpaces), "ClearMovedTwoSpaces test");


    test->assert_true(ChessPieceHelpers::IsKnight(whiteKnight), "whiteKnight is a knight");
    test->assert_false(ChessPieceHelpers::IsEmptySquare(whiteKnight), "whiteKnight is not a empty square");
    test->assert_false(ChessPieceHelpers::IsPawn(whiteKnight), "whiteKnight is not a pawn");
    test->assert_false(ChessPieceHelpers::IsBishop(whiteKnight), "whiteKnight is not a bishop");
    test->assert_false(ChessPieceHelpers::IsCastle(whiteKnight), "whiteKnight is not a castle");
    test->assert_false(ChessPieceHelpers::IsQueen(whiteKnight), "whiteKnight is not a queen");
    test->assert_false(ChessPieceHelpers::IsKing(whiteKnight), "whiteKnight is not a king");
    test->assert_true(ChessPieceHelpers::IsWhite(whiteKnight), "whiteKnight is white");
    test->assert_false(ChessPieceHelpers::IsBlack(whiteKnight), "whiteKnight is not block");

    test->assert_true(ChessPieceHelpers::IsKnight(blackKnight), "blackKnight is a knight");
    test->assert_true(ChessPieceHelpers::IsBlack(blackKnight), "blackKnight is black");
    test->assert_false(ChessPieceHelpers::IsWhite(blackKnight), "blackKnight is not white");

    test->assert_true(ChessPieceHelpers::IsBishop(blackBishopHasMoved), "blackBishopHasMoved is a bishop");
    test->assert_false(ChessPieceHelpers::IsEmptySquare(blackBishopHasMoved), "blackBishopHasMoved is not an emptySquare");
    test->assert_false(ChessPieceHelpers::IsPawn(blackBishopHasMoved), "blackBishopHasMoved is not a pawn");
    test->assert_false(ChessPieceHelpers::IsKnight(blackBishopHasMoved), "blackBishopHasMoved is not a knight");
    test->assert_false(ChessPieceHelpers::IsCastle(blackBishopHasMoved), "blackBishopHasMoved is not a castle");
    test->assert_false(ChessPieceHelpers::IsQueen(blackBishopHasMoved), "blackBishopHasMoved is not a queen");
    test->assert_false(ChessPieceHelpers::IsKing(blackBishopHasMoved), "blackBishopHasMoved is not a king");
    test->assert_true(ChessPieceHelpers::IsBlack(blackBishopHasMoved), "blackBishopHasMoved is black");
    test->assert_false(ChessPieceHelpers::IsWhite(blackBishopHasMoved), "blackBishopHasMoved is not white");
    test->assert_false(ChessPieceHelpers::HasNotMoved(blackBishopHasMoved), "blackBishopHasMoved has not moved");
    test->assert_true(ChessPieceHelpers::HasMoved(blackBishopHasMoved), "blackBishopHasMoved is not has moved");

    test->assert_true(ChessPieceHelpers::IsCastle(castleHasNotMoved), "castleHasNotMoved is a castle");
    test->assert_false(ChessPieceHelpers::IsEmptySquare(castleHasNotMoved), "castleHasNotMoved is not a EmptySquare");
    test->assert_false(ChessPieceHelpers::IsPawn(castleHasNotMoved), "castleHasNotMoved is not a pawn");
    test->assert_false(ChessPieceHelpers::IsKnight(castleHasNotMoved), "castleHasNotMoved is not a knight");
    test->assert_false(ChessPieceHelpers::IsBishop(castleHasNotMoved), "castleHasNotMoved is not a bishop");
    test->assert_false(ChessPieceHelpers::IsQueen(castleHasNotMoved), "castleHasNotMoved is not a queen");
    test->assert_false(ChessPieceHelpers::IsKing(castleHasNotMoved), "castleHasNotMoved is not a king");
    test->assert_true(ChessPieceHelpers::HasNotMoved(castleHasNotMoved), "castleHasNotMoved has not moved");
    test->assert_false(ChessPieceHelpers::HasMoved(castleHasNotMoved), "castleHasNotMoved is not has moved");

    test->assert_true(ChessPieceHelpers::IsCastle(castleHasMoved), "castleHasMoved is a castle");
    test->assert_false(ChessPieceHelpers::HasNotMoved(castleHasMoved), "castleHasMoved is not has not moved");
    test->assert_true(ChessPieceHelpers::HasMoved(castleHasMoved), "castleHasMoved has moved");

    test->assert_false(ChessPieceHelpers::IsEmptySquare(queen), "queen is not an EmptySquare");
    test->assert_false(ChessPieceHelpers::IsPawn(queen), "queen is not a pawn");
    test->assert_false(ChessPieceHelpers::IsKnight(queen), "queen is not a knight");
    test->assert_false(ChessPieceHelpers::IsBishop(queen), "queen is not a bishop");
    test->assert_false(ChessPieceHelpers::IsCastle(queen), "queen is not a castle");
    test->assert_true(ChessPieceHelpers::IsQueen(queen), "queen is a queen");
    test->assert_false(ChessPieceHelpers::IsKing(queen), "queen is not a king");

    test->assert_false(ChessPieceHelpers::IsEmptySquare(king), "king is not an EmptySquare");
    test->assert_false(ChessPieceHelpers::IsPawn(king), "king is not a pawn");
    test->assert_false(ChessPieceHelpers::IsKnight(king), "king is not a knight");
    test->assert_false(ChessPieceHelpers::IsBishop(king), "king is not a bishop");
    test->assert_false(ChessPieceHelpers::IsCastle(king), "king is not a castle");
    test->assert_false(ChessPieceHelpers::IsQueen(king), "king is not a queen");
    test->assert_true(ChessPieceHelpers::IsKing(king), "king is a king");

    test->assert_true(ChessPieceHelpers::GetPieceType(king) == ChessPieceTypes::King, "GetPieceType returns the correct type");

    ChessPiece whiteQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, false, false, false);
    test->assert_true(ChessPieceHelpers::PiecesAreSameColor(whiteKnight, whiteQueen), "whiteKnight and whiteQueen are the same color");
    test->assert_false(ChessPieceHelpers::PiecesAreSameColor(whiteKnight, blackKnight), "whiteKnight and blackKnight are not the same color");
    test->assert_true(ChessPieceHelpers::PiecesAreSameColor(blackKnight, blackBishopHasMoved), "blackKnight and blackBishopHasMoved are the same color");
    test->assert_false(ChessPieceHelpers::PiecesAreSameColor(blackKnight, emptySquare), "black piece and emptySquare are not the same color");
    test->assert_false(ChessPieceHelpers::PiecesAreSameColor(whiteKnight, emptySquare), "white piece and emptySquare are not the same color");

    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, true, false);
    ChessPiece blackQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, true, true, false);
    ChessPiece blackQueenClone = ChessPieceHelpers::ChangePieceType(blackPawn, ChessPieceTypes::Queen);
    test->assert_true(blackQueen == blackQueenClone, "ChangePieceType changes type but not other properties");

};
