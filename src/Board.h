#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <ostream>
#include <vector>

class Board {
 public:
  Board();

  Board(std::vector<std::vector<uint8_t>> const& rows);

  ~Board();

  void Clear();

  uint8_t Get(uint8_t i, uint8_t j);

  void Update(uint8_t i, uint8_t j, uint8_t val);

  std::vector<std::vector<uint8_t>> const& Rows();
  std::vector<std::vector<uint8_t>> const& Cols();
  std::vector<std::vector<uint8_t>> const& Subgrids();

  friend bool operator==(Board const& lhs, Board const& rhs);

  friend std::ostream& operator<<(std::ostream &os, Board const& board);
 private:
  std::vector<std::vector<uint8_t>> rows_;
  std::vector<std::vector<uint8_t>> cols_;
  std::vector<std::vector<uint8_t>> subgrids_;
};


#endif