// A test object is used by the test to make assertions and determines whether
// the test passes or fails.
#pragma once
#include <string>

class Test
{
public:
    void assert_true(bool statement, const char* message);
    void assert_false(bool statement, const char* message);
    bool passed() const;
    void set_name(const char* name);
private:
    bool m_failed;
    std::string m_name;
};
