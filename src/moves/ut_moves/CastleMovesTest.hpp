#include <memory>
#include "../../../test/Test.hpp"

class CastleMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void CanNotMoveOffBoardTest(std::shared_ptr<Test> test);
    void CanNotMovePastFriendlyPieceTest(std::shared_ptr<Test> test);
    void CanCaptureOpposingPieceTest(std::shared_ptr<Test> test);
};
