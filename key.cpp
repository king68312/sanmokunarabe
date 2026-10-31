#include "key.h"

#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

void enableRawMode() {  // ここでは、端末を生のモードに設定するために termios
                        // 構造体を使用しています。生のモードでは、入力が即座に取得され、エコーが無効になります。
  termios term;
  tcgetattr(STDIN_FILENO, &term);    // 現在の端末設定を取得
  term.c_lflag &= ~(ICANON | ECHO);  // ICANONを無効にして、入力を即座に取得する
  term.c_cc[VMIN] = 1;               // 最小入力文字数を1に設定
  term.c_cc[VTIME] = 0;              // タイムアウトを無効に設定
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);  // 端末設定を即座に反映
}

void disableRawMode() {
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |=
      (ICANON | ECHO);  // ICANONを有効にして、入力をバッファリングする
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

Key readKey() {
  char cmd;
  std::cin.get(cmd);
  if (cmd == 27) {
    std::cin.get(cmd);
    std::cin.get(cmd);
    if (cmd == 'A') return Key::kUp;
    if (cmd == 'B') return Key::kDown;
    if (cmd == 'C') return Key::kRight;
    if (cmd == 'D') return Key::kLeft;
  }
  if (cmd == '\n' || cmd == ' ') return Key::kEnter;  // Enter かスペース (追加)
  if (cmd == 'q') return Key::kQuit;
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

// ---- 前の main (key.cpp だけで動かしていたとき)。main は main.cpp
// にあるので使わない ---- int main() {
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
