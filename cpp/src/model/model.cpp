#include "model.h"

#include <string>
#include <vector>

int toIndex(Position pos) { return pos.row * 3 + pos.col; }

std::string judge(std::vector<std::string> board) {
  for (int i = 0; i < 8; i++) {
    if ((board[LINES[i][0]] == "x" ||
         board[LINES[i][0]] ==
             "o") &&  // 先頭の要素が"x"か"o"であることを確認、その後に全ての要素が一致するかを確認
        board[LINES[i][0]] == board[LINES[i][1]] &&
        board[LINES[i][1]] == board[LINES[i][2]]) {
      return board[LINES[i][0]];
    }
  }
  return "";
}
