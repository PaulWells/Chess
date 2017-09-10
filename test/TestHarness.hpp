#pragma once
#include <vector>

class Test;

// TestHarness manages multiple test objects and reports the results.
class TestHarness
{
public:
    TestHarness();
    std::shared_ptr<Test> NewTest();
    void OnTestsComplete() const;

private:
    std::unique_ptr<std::vector<std::shared_ptr<Test>>> m_tests;
};
