#include "../ChessPieceTypes.hpp"
#include "../ChessPieceHelpers.hpp"
#include "ChessPieceTypesTest.hpp"
#include <iostream>
#include "../../../test/TerminalColors.hpp"

void ChessPieceTypesTest::RunTests()
{
    std::cout << "Running ChessPieceTypes Tests\n";

    if (ChessPieceHelpers::IsEmptySquare(0x00) &&
        !ChessPieceHelpers::IsPawn(0x00) &&
        ChessPieceHelpers::IsPawn(0x01))
    {
        std::cout << TerminalColor::Green << "Test Passed\n" << TerminalColor::Reset;
    }
    else
    {
        std::cout << TerminalColor::Red << "Test Failed\n" << TerminalColor::Reset;
    }
}
