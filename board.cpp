#include <iostream>
#include <vector>

using namespace std;

struct Mark {
  string o;
  string x;
};

void printBoard(vector<string> board);

int main() {
  vector<string> board(9);
  cout << "Enter your mark" << endl;
  for (string &x : board) {
    cin >> x;
    // board.push_back(x); // board.push_back(x);
  }
  // for (int i = 0; i < 9; i++) {
  //   cin >> board[i];
  // }
  // ここで入力してるはずなのに出力がされない！！
  // for (int i = 0; i < 9; i++) {
  //   cout << board[i] << " ";
  // }
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
  // printBoard(board);
}

void printBoard(vector<string> board) {
  for (int i = 0; i < 9; i++) {
    cout << board[i] << " " << "|";
    if ((i + 1) % 3 == 0) {
      cout << "---------" << endl;
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
