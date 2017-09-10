#include <iostream>
#include "Test.hpp"
#include "TerminalColors.hpp"

void Test::assert_true(bool statement, const char* message)
{
    if (!statement)
    {
        std::cout << TerminalColor::Red << message << TerminalColor::Reset << std::endl;
        m_failed = true;
    }
}

void Test::assert_false(bool statement, const char* message)
{
    assert_true(!statement, message);
}

bool Test::passed() const
{
    return !m_failed;
}
