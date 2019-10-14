#include "Sudoku.h"

#include <bitset>

Sudoku::Sudoku() {}

Sudoku::Sudoku(std::vector<std::vector<uint8_t>> const& rows)
    : board_(rows) {}

Sudoku::~Sudoku() {}

void Sudoku::Clear() {
  board_.Clear();
}

bool Sudoku::Check() {
  return check(board_.Rows()) && \
         check(board_.Cols()) && \
         check(board_.Subgrids());
}

bool Sudoku::Check(uint8_t i, uint8_t j) {
  return check(board_.Rows()[i]) && \
         check(board_.Cols()[j]) && \
         check(board_.Subgrids()[i / 3 * 3 + j / 3]);
}

void Sudoku::Update(uint8_t i, uint8_t j, uint8_t val) {
  board_.Update(i, j, val);
}

bool Sudoku::Solve() {
  std::stack<std::pair<uint8_t,uint8_t>> emptyCells;
  for (uint8_t i = 0; i < 9; ++i) {
    for (uint8_t j = 0; j < 9; ++j) {
      if (board_.Get(i, j) == 0) {
        emptyCells.push({i, j});
      }
    }
  }

  return solve(emptyCells);
}

bool Sudoku::solve(std::stack<std::pair<uint8_t,uint8_t>>& emptyCells) {
  if (emptyCells.empty()) {
    return true;
  }

  auto [i, j] = emptyCells.top(); emptyCells.pop();
  for (uint8_t k = 1; k <= 9; ++k) {
    board_.Update(i, j, k);
    if (!Check(i, j)) {
      continue;
    }

    if (solve(emptyCells)) {
      return true;
    }
  }

  board_.Update(i, j, 0);
  emptyCells.push({i, j});
  return false;
}

bool Sudoku::check(std::vector<std::vector<uint8_t>> const& components) {
  for (auto& component : components) {
    if (!check(component)) {
      return false;
    }
  }

  return true;
}

bool Sudoku::check(std::vector<uint8_t> const& component) {
  std::bitset<10> s;
  for (uint8_t x : component) {
    if (x == 0) {
      continue;
    }

    if (s.test(x)) {
      return false;
    }

    s.set(x);
  }

  return true;
}

bool operator==(Sudoku const& lhs, Sudoku const& rhs) {
  return lhs.board_ == rhs.board_;
}

bool operator!=(Sudoku const& lhs, Sudoku const& rhs) {
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream &os, Sudoku const& sudoku) {
  return os << sudoku.board_;
}
