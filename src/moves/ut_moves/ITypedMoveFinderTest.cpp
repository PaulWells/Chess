#include <vector>
#include "../../types/Move.hpp"
#include "ITypedMoveFinderTest.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"
#include "../KnightMoveFinder.hpp"
#include "../QueenMoveFinder.hpp"
#include "../PawnMoveFinder.hpp"
#include "../KingMoveFinder.hpp"
#include "../CastleMoveFinder.hpp"
#include "../BishopMoveFinder.hpp"


void ITypedMoveFinderTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("ITypedMoveFinderTest");

    ITypedFinderReturnsCorrectType(test);
}

void ITypedMoveFinderTest::ITypedFinderReturnsCorrectType(std::shared_ptr<Test> test)
{
    std::unique_ptr<ITypedMoveFinder> knightMoveFinder = std::make_unique<KnightMoveFinder>();
    std::unique_ptr<ITypedMoveFinder> castleMoveFinder = std::make_unique<CastleMoveFinder>();
    std::unique_ptr<ITypedMoveFinder> bishopMoveFinder = std::make_unique<BishopMoveFinder>();
    std::unique_ptr<ITypedMoveFinder> queenMoveFinder = std::make_unique<QueenMoveFinder>();
    std::unique_ptr<ITypedMoveFinder> pawnMoveFinder = std::make_unique<PawnMoveFinder>();
    std::unique_ptr<ITypedMoveFinder> kingMoveFinder = std::make_unique<KingMoveFinder>();

    test->assert_true(knightMoveFinder->GetPieceType() == ChessPieceTypes::Knight, "KnightMoveFinderTest has a piece type of Knight");
    test->assert_true(castleMoveFinder->GetPieceType() == ChessPieceTypes::Castle, "CastleMoveFinderTest has a piece type of Castle");
    test->assert_true(bishopMoveFinder->GetPieceType() == ChessPieceTypes::Bishop, "BishopMoveFinderTest has a piece type of Bishop");
    test->assert_true(queenMoveFinder->GetPieceType() == ChessPieceTypes::Queen, "QueenMoveFinderTest has a piece type of Queen");
    test->assert_true(pawnMoveFinder->GetPieceType() == ChessPieceTypes::Pawn, "PawnMoveFinderTest has a piece type of Pawn");
    test->assert_true(kingMoveFinder->GetPieceType() == ChessPieceTypes::King, "KingMoveFinderTest has a piece type of King");
}
