cmake_minimum_required(VERSION 3.19)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 benchmark.cpp TBTree.hpp TItem.hpp TVector.hpp)