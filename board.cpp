#include <iostream>
#include <vector>

using namespace std;

void printBoard(vector<string> board);

int main() {
  vector<string> board(9);
  cout << "Enter your mark" << endl;

  // for (string &x : board) {
  //   cin >> x;
  // }

  // for (int i = 0; i < 9; i++) {
  //   cin >> board[i];
  // }
  // ここで入力してるはずなのに出力がされない！！
  // for (int i = 0; i < 9; i++) {
  //   cout << board[i] << " ";
  // }
  while (true) {
    // マークがそろったことを確認する
    // 横一列
    if (board[0] == "x" && board[1] == "x" && board[2] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[3] == "x" && board[4] == "x" && board[5] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[6] == "x" && board[7] == "x" && board[8] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[0] == "o" && board[1] == "o" && board[2] == "o") {
      cout << "Player O wins!" << endl;
      break;
    } else if (board[3] == "o" && board[4] == "o" && board[5] == "o") {
      cout << "Player O wins!" << endl;
      break;
    } else if (board[6] == "o" && board[7] == "o" && board[8] == "o") {
      cout << "Player O wins!" << endl;
      break;
      // 縦一列
    } else if (board[0] == "x" && board[3] == "x" && board[6] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[1] == "x" && board[4] == "x" && board[7] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[2] == "x" && board[5] == "x" && board[8] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[0] == "o" && board[3] == "o" && board[6] == "o") {
      cout << "Player O wins!" << endl;
      break;
    } else if (board[1] == "o" && board[4] == "o" && board[7] == "o") {
      cout << "Player O wins!" << endl;
      break;
    } else if (board[2] == "o" && board[5] == "o" && board[8] == "o") {
      cout << "Player O wins!" << endl;
      break;

      // 斜め一列
    } else if (board[0] == "x" && board[4] == "x" && board[8] == "x") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[2] == "x" && board[4] == "x" && board[6] == "x") {
      break;
    } else if (board[0] == "o" && board[4] == "o" && board[8] == "o") {
      cout << "Player X wins!" << endl;
      break;
    } else if (board[2] == "o" && board[4] == "o" && board[6] == "o") {
      break;
    }

    printBoard(board);
  }
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
