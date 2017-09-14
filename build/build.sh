# Command for building source files of project.
g++ $SRC_PATH/main.cpp $SRC_PATH/moves/*.cpp -o $BIN_PATH/main -std=c++1y
echo "Build complete"
