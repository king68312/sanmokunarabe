#include <iostream>
#include <vector>

using namespace std;

struct Mark {
  string o;
  string x;
};

void printBoard(vector<vector<string>> board);

int main() {
  // Mark型の2次元配列を作成
  vector<vector<string>> board(3, vector<string>(3, " "));

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << "Enter your mark" << endl;
      cin >> board[i][j];
    }
  }
  printBoard(board);
}

void printBoard(vector<vector<string>> board) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << board[i][j] << " " << "|";
    }
    cout << endl;
    if (i < 2)
      cout << "---------" << endl;
  }
}
