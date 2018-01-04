#include <iostream>
#include "../src/util/TerminalColor.hpp"

#include <memory>
#include "Test.hpp"

Test::Test()
{
    m_failed = false;
}

void Test::assert_true(bool statement, const char* message)
{
    if (!statement)
    {
        std::cout << TerminalColor::Red() << m_name << ": " << message << TerminalColor::Reset() << std::endl;
        m_failed = true;
    }
}

void Test::set_name(const char* name)
{
    std::cout << "Starting test: " << name << std::endl;
    m_name = std::string(name);
}

void Test::assert_false(bool statement, const char* message)
{
    assert_true(!statement, message);
}

bool Test::passed() const
{
    return !m_failed;
}
