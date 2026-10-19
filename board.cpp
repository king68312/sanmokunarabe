#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void printBoard(vector<string> board);
void playGame();
void retry();

const int LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
    {0, 4, 8}, {2, 4, 6}             // diagonals
};

string judge(vector<string> board) {
  for (int i = 0; i < 8; i++) {
    if ((board[LINES[i][0]] == "x" ||
         board[LINES[i][0]] ==
             "o") && // 先頭の要素が"x"か"o"であることを確認、その後に全ての要素が一致するかを確認
        board[LINES[i][0]] == board[LINES[i][1]] &&
        board[LINES[i][1]] == board[LINES[i][2]]) {
      return board[LINES[i][0]];
    }
  }
  return "";
}

int main() {
  cout << "三目並べゲームを開始します。" << endl;
  playGame();
  return 0;
}

void playGame() {
  vector<string> board(9, " ");
  // oのターン、xのターンを交互に繰り返す
  // for (string &x : board) {
  //   cin >> x;
  // }
  int pos;
  board[4] = "o"; // 初期状態で中央にoを置く
  for (int i = 0; i < 8; i++) {
    printBoard(board);
    cout << "マス番号を入力してください(0~8): ";
    if (cin >> pos && pos >= 0 && pos < 9 && board[pos] == " ") {
      // 入力が有効な場合のみ処理を続行
      if (i % 2 == 0) {
        board[pos] = "x";
      } else {
        board[pos] = "o";
      }
    } else {
      cout << "無効な入力です。もう一度入力してください。" << endl;
      i--; // ターンをやり直す
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    // x先行でそのあとはoと交互に入力する
    if (judge(board) != "") {
      printBoard(board);
      cout << "勝者は: " << judge(board) << endl;
      retry();
    }
  }
  printBoard(board);
  cout << "引き分け" << endl;
  retry();
}

void retry() {
  char choice;
  cout << "もう一度プレイしますか？(y/n): ";
  cin >> choice;
  if (choice == 'y' || choice == 'Y') {
    playGame();
  } else {
    cout << "ゲームを終了します。" << endl;
    exit(0);
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
}
