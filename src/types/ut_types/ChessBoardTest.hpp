#include <memory>
#include "../../../test/Test.hpp"

class ChessBoardTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void ClearBoardTest(std::shared_ptr<Test> test);
    void PieceAtTest(std::shared_ptr<Test> test);
    void OnBoardTest(std::shared_ptr<Test> test);
    void SquareEqualityTest(std::shared_ptr<Test> test);
    void GetTargetSquareTest(std::shared_ptr<Test> test);

};
