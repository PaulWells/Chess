#include <memory>
#include "../../../test/Test.hpp"

class MoveFinderTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void EmptySquaresHaveNoMoves(std::shared_ptr<Test> test);
    void FindsMovesForAllPiecesOfCorrectColor(std::shared_ptr<Test> test);
};
