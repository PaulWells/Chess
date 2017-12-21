#include <vector>
#include "../../types/Move.hpp"
#include "SquareUnderAttackDeterminerTest.hpp"
#include "../MoveFinder.hpp"
#include "MoveTestHelpers.hpp"


void SquareUnderAttackDeterminerTest::RunTests(std::shared_ptr<Test> test)
{
    test->set_name("SquareUnderAttackDeterminerTest");

    EmptyBoardTest(test);
}

void SquareUnderAttackDeterminerTest::EmptyBoardTest(std::shared_ptr<Test> test)
{
    
}
