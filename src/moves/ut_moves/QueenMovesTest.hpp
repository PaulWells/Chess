#include <memory>
#include "../../../test/Test.hpp"

class QueenMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void QueenMovesBothStraightAndDiagonally(std::shared_ptr<Test> test);
};
