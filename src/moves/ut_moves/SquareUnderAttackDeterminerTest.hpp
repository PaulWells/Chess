#include <memory>
#include "../../../test/Test.hpp"

class SquareUnderAttackDeterminerTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void EmptyBoardTest(std::shared_ptr<Test> test);
};
