#include "Board.h"

Board::Board()
    : rows_(9, std::vector<uint8_t>(9, 0)),
      cols_(9, std::vector<uint8_t>(9, 0)),
      subgrids_(9, std::vector<uint8_t>(9, 0)) {}

Board::Board(std::vector<std::vector<uint8_t>> const& rows)
    : rows_(9, std::vector<uint8_t>(9, 0)),
      cols_(9, std::vector<uint8_t>(9, 0)),
      subgrids_(9, std::vector<uint8_t>(9, 0)) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; j++) {
      Update(i, j, rows[i][j]);
    }
  }
}

Board::~Board() {}

void Board::Clear() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      rows_[i][j] = cols_[i][j] = subgrids_[i][j] = 0;
    }
  }
}

uint8_t Board::Get(uint8_t i, uint8_t j) {
  return rows_[i][j];
}

void Board::Update(uint8_t i, uint8_t j, uint8_t val) {
  rows_[i][j] = cols_[j][i] = subgrids_[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] = val;
}

std::vector<std::vector<uint8_t>> const& Board::Rows() { return rows_; }

std::vector<std::vector<uint8_t>> const& Board::Cols() { return cols_; }

std::vector<std::vector<uint8_t>> const& Board::Subgrids() { return subgrids_; }

bool operator==(Board const& lhs, Board const& rhs) {
  return lhs.rows_ == rhs.rows_;
}
