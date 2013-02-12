# Project Name
project(Graphics)

# States that CMake required version must be >= 2.6
cmake_minimum_required(VERSION 2.6)

# set includ directories
include_directories(${Graphics_SOURCE_DIR}/include)
include_directories(${Graphics_SOURCE_DIR}/my_include)

# get CPP files
file(GLOB SRC src/*cpp)
file(GLOB MY_SRC my_src/*cpp)

# create executables
SET(EXECLIST test hw1 imagediff hw2 hw3)

foreach(EXEC ${EXECLIST})
  add_executable(${EXEC} ${SRC} ${MY_SRC} bin/${EXEC}.cpp)
endforeach(EXEC)


