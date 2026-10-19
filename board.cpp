#include <iostream>
#include <vector>

using namespace std;

void printBoard(vector<string> board);

const int LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
    {0, 4, 8}, {2, 4, 6}             // diagonals
};

bool judge(vector<string> board) {
  // 縦横斜めに一致するものがあればTrue,それ以外はFalseを返す
  for (int i = 0; i < 8; i++) {
    if ((board[LINES[i][0]] == "x" ||
         board[LINES[i][0]] ==
             "o") && // 先頭の要素が"x"か"o"であることを確認、その後に全ての要素が一致するかを確認
        board[LINES[i][0]] == board[LINES[i][1]] &&
        board[LINES[i][1]] == board[LINES[i][2]]) {
      return true;
    }
  }
  return false;
}

int main() {
  vector<string> board(9);

  for (string &x : board) {
    cin >> x;
  }

  // for (int i = 0; i < 9; i++) {
  //   cin >> board[i];
  // }
  // ここで入力してるはずなのに出力がされない！！
  // for (int i = 0; i < 9; i++) {
  //   cout << board[i] << " ";
  // }

  if (judge(board)) {
    cout << "勝者あり" << endl;
  } else {
    cout << "勝者なし" << endl;
  }
  printBoard(board);
}
void printBoard(vector<string> board) {

  for (int i = 0; i < 9; i++) {
    cout << board[i] << " " << " ";
    if (i % 3 != 2) {
      cout << "|";
    } else {
      cout << endl;
      if (i != 8) {
        cout << "---------" << endl;
      }
    }
  }
  // for (int i = 0; i < 3; i++) {
  //   for (int j = 0; j < 3; j++) {
  //     cout << board[i][j] << " " << "|";
  //   }
  //   cout << endl;
  //   if (i < 2)
  //     cout << "---------" << endl;
  // }
}
