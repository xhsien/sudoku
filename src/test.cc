#include "Sudoku.h"

#include <iostream>
#include <vector>

int main() {

  Sudoku sudoku;
  sudoku.Update(0, 0, 8);
  sudoku.Update(1, 2, 3);
  sudoku.Update(1, 3, 6);
  sudoku.Update(2, 1, 7);
  sudoku.Update(2, 4, 9);
  sudoku.Update(2, 6, 2);
  sudoku.Update(3, 1, 5);
  sudoku.Update(3, 5, 7);
  sudoku.Update(4, 4, 4);
  sudoku.Update(4, 5, 5);
  sudoku.Update(4, 6, 7);
  sudoku.Update(5, 3, 1);
  sudoku.Update(5, 7, 3);
  sudoku.Update(6, 2, 1);
  sudoku.Update(6, 7, 6);
  sudoku.Update(6, 8, 8);
  sudoku.Update(7, 2, 8);
  sudoku.Update(7, 3, 5);
  sudoku.Update(7, 7, 1);
  sudoku.Update(8, 1, 9);
  sudoku.Update(8, 6, 4);
  sudoku.Solve();

  Sudoku solution(
       {{8, 1, 2, 7, 5, 3, 6, 4, 9},
        {9, 4, 3, 6, 8, 2, 1, 7, 5},
        {6, 7, 5, 4, 9, 1, 2, 8, 3},
        {1, 5, 4, 2, 3, 7, 8, 9, 6},
        {3, 6, 9, 8, 4, 5, 7, 2, 1},
        {2, 8, 7, 1, 6, 9, 5, 3, 4},
        {5, 2, 1, 9, 7, 4, 3, 6, 8},
        {4, 3, 8, 5, 2, 6, 9, 1, 7},
        {7, 9, 6, 3, 1, 8, 4, 5, 2}});

  if (sudoku != solution) {
    std::cout << "Actual:   \n" << sudoku << std::endl;
    std::cout << "Expected: \n" << solution << std::endl;
    return 1;
  }

  return 0;
}