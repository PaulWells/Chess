#include <memory>
#include "../../../test/Test.hpp"

class ITypedMoveFinderTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void ITypedFinderReturnsCorrectType(std::shared_ptr<Test> test);
};
