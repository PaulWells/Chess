#include "../ChessPieceTypes.hpp"
#include "../ChessPieceHelpers.hpp"
#include "ChessPieceTypesTest.hpp"
#include <iostream>

void ChessPieceTypesTest::RunTests()
{
    std::cout << "Running ChessPieceTypes Tests\n";

    if (ChessPieceHelpers::IsEmptySquare(0x00) &&
        !ChessPieceHelpers::IsPawn(0x00) &&
        ChessPieceHelpers::IsPawn(0x01))
    {
        std::cout << "Test Passed\n";
    }
    else
    {
        std::cout << "Test Failed\n";
    }
}
