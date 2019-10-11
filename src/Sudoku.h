#ifndef SUDOKU_H
#define SUDOKU_H

#include "Board.h"

#include <cstdint>
#include <vector>

class Sudoku {
 public:
  Sudoku();

  ~Sudoku();

  // Clears the entire board.
  void Clear();

  // Checks the board for any violations.
  //
  // @return true if there is no violations.
  bool Check();

  // Updates the value of a cell. If val is 0, then the cell (i,j) becomes empty.
  void Update(uint8_t i, uint8_t j, uint8_t val);

  // Solves the board by filling up all empty cells.
  //
  // @return true if the board has at least one solution.
  bool Solve();

  // Prints the board.
  void Print();
 private:
  bool check(const std::vector<std::vector<uint8_t>>& component);

  Board board;
};


#endif