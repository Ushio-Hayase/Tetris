cmake_minimum_required(VERSION 3.15)
project(tetris)

set(CXX_STANDARD 17)

add_executable(tetris main.cpp Tetris.cpp)

target_include_directories(tetris PRIVATE ../header)