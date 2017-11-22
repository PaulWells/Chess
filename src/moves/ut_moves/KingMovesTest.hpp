#include <memory>
#include "../../../test/Test.hpp"

class KingMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void KingCanOnlyMoveOneSquare(std::shared_ptr<Test> test);
};
