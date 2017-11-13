#include <iostream>
#include <memory>
#include "../src/types/ut_types/ChessPieceTest.hpp"
#include "../src/types/ut_types/ChessBoardTest.hpp"
#include "../src/moves/ut_moves/MoveFinderTest.hpp"
#include "../src/moves/ut_moves/KnightMovesTest.hpp"
#include "../src/moves/ut_moves/CastleMovesTest.hpp"
#include "../src/moves/ut_moves/BishopMovesTest.hpp"
#include "../src/moves/ut_moves/QueenMovesTest.hpp"
#include "../src/types/ChessBoard.hpp"
#include "TestHarness.hpp"

int main()
{
  std::unique_ptr<ChessPieceTest> chessPieceTest(new ChessPieceTest());
  std::unique_ptr<TestHarness> testHarness(new TestHarness());
  chessPieceTest->RunTests(testHarness->NewTest());

  std::unique_ptr<ChessBoardTest> chessBoardTest(new ChessBoardTest());
  chessBoardTest->RunTests(testHarness->NewTest());

  std::unique_ptr<MoveFinderTest> moveFinderTest(new MoveFinderTest());
  moveFinderTest->RunTests(testHarness->NewTest());

  std::unique_ptr<KnightMovesTest> knightMovesTest(new KnightMovesTest());
  knightMovesTest->RunTests(testHarness->NewTest());

  std::unique_ptr<CastleMovesTest> castleMovesTest(new CastleMovesTest());
  castleMovesTest->RunTests(testHarness->NewTest());

  std::unique_ptr<BishopMovesTest> bishopMovesTest(new BishopMovesTest());
  bishopMovesTest->RunTests(testHarness->NewTest());

  std::unique_ptr<QueenMovesTest> queenMovesTest(new QueenMovesTest());
  queenMovesTest->RunTests(testHarness->NewTest());

  testHarness->OnTestsComplete();
}
