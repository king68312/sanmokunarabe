#include "view.h"

#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "controller.h"

void saveOrigin() {  // 端末のカーソル位置を保存する
  std::cout << "\0337" << std::flush;
}  // std::flashはバッファをフラッシュするためのもので、出力を即座に表示するために使用されます。

// 端末のカーソル位置を元に戻す
void backToOrigin() { std::cout << "\0338" << std::flush; }
//\0338 ESC 8 端末のカーソル位置を保存した位置に戻す

void showCursor(Position pos) {
  backToOrigin();
  std::cout << "\033[" << (5 - pos.row * 2) << "A"  // 上に移動
            << "\033[" << (pos.col * 4 + 1) << "G"  // 左に移動
            << std::flush;
}

void printBoard(const std::vector<std::string>& board) {
  for (int i = 0; i < 9; i++) {
    std::cout << board[i] << " " << " ";
    if (i % 3 != 2) {
      std::cout << "|";
    } else {
      std::cout << std::endl;
      if (i != 8) {
        std::cout << "-----------" << std::endl;
      }
    }
  }
}
