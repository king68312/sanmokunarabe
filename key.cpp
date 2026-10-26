#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "board.h"
#include "key.h"

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

// 前: enum class Key { kUp, kDown, kLeft, kRight, kQuit };
enum class Key { kUp, kDown, kLeft, kRight, kEnter, kQuit, kOther };

struct Position {
  int row;
  int col;
};

void enableRawMode() {
  termios term;
  tcgetattr(STDIN_FILENO, &term);    // 現在の端末設定を取得
  term.c_lflag &= ~(ICANON | ECHO);  // ICANONを無効にして、入力を即座に取得する
  tcsetattr(STDIN_FILENO, TCSANOW, &term);  // 端末設定を即座に反映
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
  if (c == '\n' || c == ' ') return Key::kEnter;  // Enter かスペース (追加)
  if (c == 'q') return Key::kQuit;
  return Key::kOther;  // どれでもないキー (追加)
}

Position movePosition(Position pos, Key key) {
  if (key == Key::kUp && pos.row > 0) pos.row--;
  if (key == Key::kDown && pos.row < 2) pos.row++;
  if (key == Key::kLeft && pos.col > 0) pos.col--;
  if (key == Key::kRight && pos.col < 2) pos.col++;
  return pos;
}

// 行と列 (Position) を、board の番号 (0〜8) に変える (追加)
int toIndex(Position pos) { return pos.row * 3 + pos.col; }

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

// 矢印キーでマスを選んで、そのマスの番号 (0〜8) を返す (追加)
// printBoard で盤面を表示した直後に呼ぶ。q で中断したら -1 を返す
int selectCell(const std::vector<std::string>& board) {
  saveOrigin();  // 盤面のすぐ下を覚える
  enableRawMode();

  Position cursor{1, 1};
  showCursor(cursor);
  while (true) {
    Key key = readKey();

    if (key == Key::kQuit) {  // q: 中断して -1 を返す
      backToOrigin();
      disableRawMode();
      return -1;
    }

    if (key == Key::kEnter) {  // Enter: 空いているマスなら、その番号を返す
      int cell = toIndex(cursor);
      if (board[cell] == " ") {
        backToOrigin();
        disableRawMode();
        return cell;
      }
    }

    cursor = movePosition(cursor, key);
    showCursor(cursor);
  }
}

// ---- 前の main (key.cpp だけで動かしていたとき)。main は main.cpp にあるので使わない ----
// int main() {
//   std::vector<std::string> board(9, " ");
//   std::cout << "矢印キーで移動(q で終了)" << std::endl;
//   printBoard(board);
//   enableRawMode();  // 端末を生のモードに設定
//
//   Position cursor{1, 1};
//   showCursor(cursor);
//   while (true) {
//     Key key = readKey();
//     if (key == Key::kQuit) break;
//     cursor = movePosition(cursor, key);
//     showCursor(cursor);
//   }
//   disableRawMode();
//   return 0;
// }
// ---- ここまで ----
