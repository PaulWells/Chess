# Command for building test files of project.

# Create tests folder if it does not exist.
if [ ! -d $BIN_PATH/tests ]; then
    mkdir $BIN_PATH/tests
fi

g++ $SRC_PATH/types/ut_types/*.cpp $SRC_PATH/moves/ut_moves/*.cpp $SRC_PATH/moves/*.cpp $SRC_PATH/util/*.cpp $TEST_PATH/*.cpp -o $BIN_PATH/tests/ut_tests -std=c++1y
echo "Finished building tests"
