#include <memory>
#include "../../../test/Test.hpp"

class SquareUnderAttackDeterminerTest
{
public:
    void RunTests(std::shared_ptr<Test> test);
private:
    void EmptyBoardTest(std::shared_ptr<Test> test);
    void SquareUnderAttackDeterminerDoesNotChangeBoardState(std::shared_ptr<Test> test);
    void DetectsAttackByPawn(std::shared_ptr<Test> test);
    void DetectsAttackByKnight(std::shared_ptr<Test> test);
    void DetectsAttackByCastle(std::shared_ptr<Test> test);
    void DetectsAttackByBishop(std::shared_ptr<Test> test);
    void DetectsAttackByQueen(std::shared_ptr<Test> test);
    void DetectsAttackByKing(std::shared_ptr<Test> test);
    void DoesNotConsiderFriendlyUnitsAsAttacking(std::shared_ptr<Test> test);
};
