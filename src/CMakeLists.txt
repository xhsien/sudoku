cmake_minimum_required(VERSION 3.15.4 FATAL_ERROR)

project(sudoku CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(sudoku main.cc
                      Sudoku.cc
                      Board.cc)

add_executable(sudokuTest test.cc
                          Sudoku.cc
                          Board.cc)

add_test(test sudokuTest)
