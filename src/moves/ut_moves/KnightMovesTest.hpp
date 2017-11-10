#include <memory>
#include "../../../test/Test.hpp"

class KnightMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void EmptyBoardEveryMoveTest(std::shared_ptr<Test> test);
    void KnightCanNotMoveOffTheBoard(std::shared_ptr<Test> test);
    void KnightCanNotMoveToSquareWithPieceOfSameColor(std::shared_ptr<Test> test);
    void KnightCanCaptureOpposingPiece(std::shared_ptr<Test> test);
};
