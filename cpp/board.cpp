#include "board.h"

#include <iostream>
#include <limits>

const int LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // columns
    {0, 4, 8}, {2, 4, 6}              // diagonals
};

void printBoard(std::vector<std::string> board) {
  for (int i = 0; i < 9; i++) {
    std::cout << board[i] << " " << " ";
    if (i % 3 != 2) {
      std::cout << "|";
    } else {
      std::cout << std::endl;
      if (i != 8) {
        std::cout << "---------" << std::endl;
      }
    }
  }
}
