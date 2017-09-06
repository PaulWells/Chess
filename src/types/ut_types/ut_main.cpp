#include <iostream>
#include "ChessPieceTypesTest.hpp"

int main()
{
  std::cout << "Running Type Tests\n";
  ChessPieceTypesTest* chessPieceTypesTest = new ChessPieceTypesTest();
  chessPieceTypesTest->RunTests();
  delete chessPieceTypesTest;
}
