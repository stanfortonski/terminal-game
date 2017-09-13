cmake_minimum_required(VERSION 3.0)

project(npc_maker)

include_directories(include)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder -Wno-unused-value -std=c++14")

file(GLOB_RECURSE MODULES "../modules/*.cpp")

add_executable(npc_maker main.cpp ${MODULES})
