#include <memory>
#include "../../../test/Test.hpp"

class KingMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void KingCanOnlyMoveOneSquare(std::shared_ptr<Test> test);
    void WhiteCastlingMoveToTheRightTest(std::shared_ptr<Test> test);
    // cant castle when piece between
    // can't castle when opponent is attacking a square
};
