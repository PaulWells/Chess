#include <iostream>
#include <vector>
#include "TestHarness.hpp"
#include "TerminalColors.hpp"
#include "Test.hpp"

TestHarness::TestHarness()
{
    std::vector<std::shared_ptr<Test>>* tests = new std::vector<std::shared_ptr<Test>>();
    m_tests = std::unique_ptr<std::vector<std::shared_ptr<Test>>>(tests);
}

std::shared_ptr<Test> TestHarness::NewTest()
{
    std::shared_ptr<Test> test = std::make_shared<Test>();
    m_tests->push_back(test);
    return test;
}

void TestHarness::OnTestsComplete() const
{
    std::cout << std::endl;
    int numTestsFailed = 0;
    int numTestsPassed = 0;
    for (std::vector<std::shared_ptr<Test>>::iterator it = m_tests->begin(); it != m_tests->end(); ++it)
    {
        std::shared_ptr<Test> test = *it;
        if (test->passed())
        {
            numTestsPassed++;
        }
        else
        {
            numTestsFailed++;
        }
    }

    if (numTestsPassed > 0)
    {
        std::cout << TerminalColor::Green;
    }
    std::cout << "Tests Passed: " << numTestsPassed << std::endl << TerminalColor::Reset;

    if (numTestsFailed > 0)
    {
        std::cout << TerminalColor::Red;
    }
    std::cout << "Tests Failed: " << numTestsFailed << std::endl << TerminalColor::Reset;
}
