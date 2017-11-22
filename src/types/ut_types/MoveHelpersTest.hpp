#include <memory>
#include "../../../test/Test.hpp"

class MoveHelpersTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void CopyMoveWithPromotionTest(std::shared_ptr<Test> test);
};
