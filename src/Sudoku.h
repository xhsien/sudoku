#ifndef SUDOKU_H
#define SUDOKU_H

#include "Board.h"

#include <cstdint>
#include <ostream>
#include <stack>
#include <vector>

class Sudoku {
 public:
  Sudoku();

  Sudoku(std::vector<std::vector<uint8_t>> const& rows);

  ~Sudoku();

  // Clears the entire board.
  void Clear();

  // Checks the board for any violations.
  //
  // @return true if there is no violations.
  bool Check() const;

  // Checks the position (i,j) for any violations.
  //
  // @return true if there is no violations.
  bool Check(uint8_t i, uint8_t j) const;

  // Updates the value of a cell. If val is 0, then the cell (i,j) becomes empty.
  void Update(uint8_t i, uint8_t j, uint8_t val);

  // Solves the board by filling up all empty cells.
  //
  // @return true if the board has at least one solution.
  bool Solve();

  friend bool operator==(Sudoku const& lhs, Sudoku const& rhs);

  friend bool operator!=(Sudoku const& lhs, Sudoku const& rhs);

  friend std::ostream& operator<<(std::ostream &os, Sudoku const& sudoku);
 private:
  bool check(std::vector<std::vector<uint8_t>> const& component) const;

  bool check(std::vector<uint8_t> const& component) const;

  bool solve(std::stack<std::pair<uint8_t,uint8_t>>& emptyCells);

  Board board_;
};


#endif