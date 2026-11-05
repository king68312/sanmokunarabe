#include <iostream>

#include "controller.h"
#include "model.h"

int main() {
  std::cout << "三目並べゲームを開始します。" << std::endl;
  do {
    if (!playGame()) break;
  } while (retry());
}
