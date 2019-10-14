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

uint8_t Board::Get(uint8_t i, uint8_t j) const {
  return rows_[i][j];
}

void Board::Update(uint8_t i, uint8_t j, uint8_t val) {
  rows_[i][j] = cols_[j][i] = subgrids_[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] = val;
}

std::vector<std::vector<uint8_t>> const& Board::Rows() const { return rows_; }

std::vector<std::vector<uint8_t>> const& Board::Cols() const { return cols_; }

std::vector<std::vector<uint8_t>> const& Board::Subgrids() const { return subgrids_; }

bool operator==(Board const& lhs, Board const& rhs) {
  return lhs.rows_ == rhs.rows_;
}

std::ostream& operator<<(std::ostream &os, Board const& board) {
  os << " 123 456 789 " << std::endl;
  for (uint8_t i = 0; i < 9; ++i) {
    if (i % 3 == 0) {
      os << "-------------" << std::endl;
    }

    for (uint8_t j = 0; j < 9; ++j) {
      if (j % 3 == 0) {
        os << '|';
      }

      if (board.rows_[i][j] == 0) {
        os << " ";
      } else {
        os << unsigned(board.rows_[i][j]);
      }
    }
    os << "|" << char('1' + i) << std::endl;
  }
  os << "-------------" << std::endl;
  return os;
}
