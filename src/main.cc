#include "Sudoku.h"

#include <iostream>
#include <functional>

template <typename T, class Checker>
T PromptAndGet(std::string const& prompt, Checker isValid) {
  T value;
  do {
    std::cout << prompt;
    std::cin >> value;
  } while (!isValid(value));
  return value;
}

int main(int argc, char** argv) {
  
  Sudoku sudoku;
  while (true) {
    std::cout << "========================" << std::endl;
    std::cout << "Current Sudoku board:   " << std::endl;
    sudoku.Print();

    std::cout << "[1] Update cell.  " << std::endl;
    std::cout << "[2] Solve puzzle. " << std::endl;
    std::cout << "[3] Restart.      " << std::endl;
    std::cout << "[4] Quit.         " << std::endl;
    std::cout << "Select an action: ";

    int option;
    std::cin >> option;
    switch (option) {
      case 1: {
        int row = PromptAndGet<int>("Pick row: ", [](int row) { return 1 <= row && row <= 9; });
        int col = PromptAndGet<int>("Pick col: ", [](int col) { return 1 <= col && col <= 9; });
        int val = PromptAndGet<int>("Update value to: ", [](int val) { return 0 <= val && val <= 9; });
        sudoku.Update(row - 1, col - 1, val);
        break;
      }
      case 2: {
        if (!sudoku.Solve()) {
          std::cout << "The board is unsolvable!" << std::endl;
        }
        break;
      }
      case 3: {
        sudoku.Clear();
        break;
      }
      case 4: {
        return 0;
      }
      default: {
        std::cout << "Unknown action!" << std::endl;
      }
    }
  }

  return 0;
}