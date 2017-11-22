#include <memory>
#include "../../../test/Test.hpp"

class PawnMovesTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void StartingPositionMoveTest(std::shared_ptr<Test> test);
    void SingleForwardMoveTest(std::shared_ptr<Test> test);
    void AttackTest(std::shared_ptr<Test> test);
    void EnPassantAttackTest(std::shared_ptr<Test> test);
    void CantMoveForwardIntoOpposingPieceTest(std::shared_ptr<Test> test);
    void CantMoveIntoFriendlyPieceTest(std::shared_ptr<Test> test);
    void CantAttackOffTheBoardTest(std::shared_ptr<Test> test);
    void PromotionTest(std::shared_ptr<Test> test);
};
