#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <vector>

class Board {
 public:
  Board();

  ~Board();

  void Clear();

  uint8_t Get(uint8_t i, uint8_t j);

  void Update(uint8_t i, uint8_t j, uint8_t val);

  std::vector<std::vector<uint8_t>> const& Rows();
  std::vector<std::vector<uint8_t>> const& Cols();
  std::vector<std::vector<uint8_t>> const& Subgrids();

 private:
  std::vector<std::vector<uint8_t>> rows;
  std::vector<std::vector<uint8_t>> cols;
  std::vector<std::vector<uint8_t>> subgrids;
};


#endif