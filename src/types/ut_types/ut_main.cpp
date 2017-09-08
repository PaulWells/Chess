#include <iostream>
#include "ChessPieceTypesTest.hpp"

int main()
{
  std::cout << "Running Type Tests\n";
  std::unique_ptr<ChessPieceTypesTest> chessPieceTypesTest(new ChessPieceTypesTest());
  chessPieceTypesTest->RunTests();
}
