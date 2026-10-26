#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "board.h"

// それぞれのキーをUp Down Left Rightに対応させる
//\033[2A
//\033[2B
//\033[2C
//\033[2D

// struct Key {
//   std::string up = "\033[2A";
//   std::string down = "\033[2B";
//   std::string right = "\033[2C";
//   std::string left = "\033[2D";
// };

enum class Key { kUp, kDown, kLeft, kRight, kQuit, kOther };

struct Position {
  int row;
  int col;
};

void enableRawMode() {
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);  // ICANONを無効にして、入力を即座に取得する
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disableRawMode() {
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |=
      (ICANON | ECHO);  // ICANONを有効にして、入力をバッファリングする
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

Key readKey() {
  char c;
  read(STDIN_FILENO, &c, 1);
  if (c == 27) {
    char bracket;
    char letter;
    read(STDIN_FILENO, &bracket, 1);
    read(STDIN_FILENO, &letter, 1);
    if (letter == 'A') return Key::kUp;
    if (letter == 'B') return Key::kDown;
    if (letter == 'C') return Key::kRight;
    if (letter == 'D') return Key::kLeft;
  }
  if (c == 'q') return Key::kQuit;
  return Key::kOther;  // デフォルトで終了キーを返す
}

Position movePosition(Position pos, Key key) {
  if (key == Key::kUp && pos.row > 0) pos.row--;
  if (key == Key::kDown && pos.row < 2) pos.row++;
  if (key == Key::kLeft && pos.col > 0) pos.col--;
  if (key == Key::kRight && pos.col < 2) pos.col++;
  return pos;
}

void saveOrigin() {
  std::cout << "\0337" << std::flush;
}  // std::flashはバッファをフラッシュするためのもので、出力を即座に表示するために使用されます。

void backToOrigin() { std::cout << "\0338" << std::flush; }

void showCursor(Position pos) {
  backToOrigin();
  std::cout << "\033[" << (5 - pos.row * 2) << "A"  // 上に移動
            << "\033[" << (pos.col * 4 + 1) << "G"  // 左に移動
            << std::flush;
}

int main() {
  std::vector<std::string> board(9, " ");
  std::cout << "矢印キーで移動(q で終了)" << std::endl;
  printBoard(board);
  saveOrigin();
  enableRawMode();  // 端末を生のモードに設定

  Position cursor{0, 0};

  showCursor(cursor);
  while (true) {
    Key key = readKey();
    if (key == Key::kQuit) break;

    cursor = movePosition(cursor, key);
    showCursor(cursor);
  }

  backToOrigin();
  disableRawMode();
  std::cout << "終了します。" << std::endl;
  return 0;
}
