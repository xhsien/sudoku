#include "Sudoku.h"

#include <bitset>
#include <iostream>

Sudoku::Sudoku() {}

Sudoku::~Sudoku() {}

void Sudoku::Clear() {
  board.Clear();
}

bool Sudoku::Check() {
  return check(board.Rows()) && \
         check(board.Cols()) && \
         check(board.Subgrids());
}

void Sudoku::Update(uint8_t i, uint8_t j, uint8_t val) {
  board.Update(i, j, val);
}

bool Sudoku::Solve() {
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      if (board.Get(i, j) == 0) {
        for (uint8_t k = 1; k <= 9; ++k) {
          board.Update(i, j, k);
          if (!Check()) {
            continue;
          }

          if (Solve()) {
            return true;
          }
        }

        board.Update(i, j, 0);
        return false;
      }
    }
  }

  return true;
}

void Sudoku::Print() {
  std::cout << " 123 456 789 " << std::endl;
  for (uint8_t i = 0; i < 9; ++i) {
    if (i % 3 == 0) {
      std::cout << "=============" << std::endl;
    }

    for (uint8_t j = 0; j < 9; ++j) {
      if (j % 3 == 0) {
        std::cout << '|';
      }

      if (board.Get(i, j) == 0) {
        std::cout << " ";
      } else {
        std::cout << unsigned(board.Get(i, j));
      }
    }
    std::cout << "|" << char('1' + i) << std::endl;
  }
  std::cout << "=============" << std::endl;
}

bool Sudoku::check(const std::vector<std::vector<uint8_t>>& component) {
  for (auto& row : component) {
    std::bitset<10> s;
    for (uint8_t x : row) {
      if (x == 0) {
        continue;
      }

      if (s.test(x)) {
        return false;
      }

      s.set(x);
    }
  }

  return true;
}
