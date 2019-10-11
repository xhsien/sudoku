#include "Board.h"

Board::Board()
    : rows(9, std::vector<uint8_t>(9, 0)),
      cols(9, std::vector<uint8_t>(9, 0)),
      subgrids(9, std::vector<uint8_t>(9, 0)) {}

Board::~Board() {}

void Board::Clear() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      rows[i][j] = cols[i][j] = subgrids[i][j] = 0;
    }
  }
}

uint8_t Board::Get(uint8_t i, uint8_t j) {
  return rows[i][j];
}

void Board::Update(uint8_t i, uint8_t j, uint8_t val) {
  rows[i][j] = cols[j][i] = subgrids[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] = val;
}

std::vector<std::vector<uint8_t>> const& Board::Rows() { return rows; }

std::vector<std::vector<uint8_t>> const& Board::Cols() { return cols; }

std::vector<std::vector<uint8_t>> const& Board::Subgrids() { return subgrids; }
