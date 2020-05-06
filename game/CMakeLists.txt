cmake_minimum_required(VERSION 3.0)

project(terminal-game)

include_directories(include)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-reorder -Wno-unused-value -std=c++14 -Wno-misleading-indentation -static-libgcc -static-libstdc++")

file(GLOB_RECURSE MODULES "../modules/*.cpp")

add_executable(game main.cpp ${MODULES})