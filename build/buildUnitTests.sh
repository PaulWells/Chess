# Command for building test files of project.

# Create tests folder if it does not exist.
if [ ! -d $BIN_PATH/tests ]; then
    mkdir $BIN_PATH/tests
fi

g++ $SRC_PATH/types/ut_types/*.cpp -o $BIN_PATH/tests/ut_types -std=c++11
echo "Finished building tests"
