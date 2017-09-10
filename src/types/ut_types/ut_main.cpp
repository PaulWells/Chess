#include <iostream>
#include <memory>
#include "ChessPieceTypesTest.hpp"
#include "../../../test/TestHarness.hpp"

int main()
{

  std::cout << "Running Type Tests\n";
  std::unique_ptr<ChessPieceTypesTest> chessPieceTypesTest(new ChessPieceTypesTest());
  std::unique_ptr<TestHarness> testHarness(new TestHarness());
  chessPieceTypesTest->RunTests(testHarness->NewTest());
  testHarness->OnTestsComplete();
}
