#include <iostream>
#include <memory>
#include "../src/types/ut_types/ChessPieceTest.hpp"
#include "../src/types/ut_types/ChessBoardTest.hpp"
#include "../src/types/ChessBoard.hpp"
#include "TestHarness.hpp"

int main()
{
  std::cout << "Running Type Tests\n";

  std::unique_ptr<ChessPieceTest> chessPieceTest(new ChessPieceTest());
  std::unique_ptr<TestHarness> testHarness(new TestHarness());
  chessPieceTest->RunTests(testHarness->NewTest());

  std::unique_ptr<ChessBoardTest> chessBoardTest(new ChessBoardTest());
  chessBoardTest->RunTests(testHarness->NewTest());

  testHarness->OnTestsComplete();
}
