#include <memory>
#include "../../../test/Test.hpp"

class BishopMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void BishopMovesDiagonallyTest(std::shared_ptr<Test> test);
};
