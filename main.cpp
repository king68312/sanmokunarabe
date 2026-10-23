#include <iostream>

#include "board.h"

int main() {
  std::cout << "三目並べゲームを開始します。" << std::endl;
  do {
    playGame();
  } while (retry());
  return 0;
}
