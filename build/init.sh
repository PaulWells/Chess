#!/bin/bash

# Set PROJECT_ROOT which is the top folder of the project.
# Assumes the project name is "Chess"
currentDirectory=$(pwd);
index=$(echo $(pwd) | awk '{print index($0, "Chess")}');
index=$(expr $index + 5);
PROJECT_ROOT=$(echo $(pwd)| cut -c 1-$index);
export PROJECT_ROOT
echo "PROJECT_ROOT:" $PROJECT_ROOT;

# Set BUILD_PATH and add to path
BUILD_PATH=$PROJECT_ROOT"build";
export PATH=$BUILD_PATH:$PATH
export BUILD_PATH
echo "BUILD_PATH:" $BUILD_PATH;

# Set BIN_PATH
BIN_PATH=$PROJECT_ROOT"bin";
export PATH=$BIN_PATH:$PATH
export BIN_PATH
echo "BIN_PATH:" $BIN_PATH;

# Set SRC_PATH
SRC_PATH=$PROJECT_ROOT"src";
export SRC_PATH
echo "SRC_PATH:" $SRC_PATH;
