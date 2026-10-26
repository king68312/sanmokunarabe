#include "board.h"

#include <iostream>
#include <limits>

#include "key.h"

const int LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // columns
    {0, 4, 8}, {2, 4, 6}              // diagonals
};

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

void playGame() {
  std::vector<std::string> board(9, " ");
  // oのターン、xのターンを交互に繰り返す
  int pos;
  board[4] = "o";  // 初期状態で中央にoを置く
  for (int i = 0; i < 8; i++) {
    std::cout << "矢印キーで移動(q で終了)" << std::endl;
    printBoard(board);
    pos = selectCell(board);
    if (pos == -1) {
      std::cout << "ゲームを終了します。" << std::endl;
      return;
    }
    // ---- 前のコード (数字で入力していたとき) ----
    // std::cout << "マス番号を入力してください(0~8): ";
    // if (std::cin >> pos && pos >= 0 && pos < 9 && board[pos] == " ") {
    //   // 入力が有効な場合のみ処理を続行
    //   if (i % 2 == 0) {
    //     board[pos] = "x";
    //   } else {
    //     board[pos] = "o";
    //   }
    // } else {
    //   std::cout << "無効な入力です。もう一度入力してください。" << std::endl;
    //   i--;  // ターンをやり直す
    //   std::cin.clear();
    //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //   continue;
    // }
    // ---- ここまで ----

    // selectCell は空いているマスしか返さないので、そのまま置く (追加)
    if (i % 2 == 0) {
      board[pos] = "x";
    } else {
      board[pos] = "o";
    }

    // x先行でそのあとはoと交互に入力する
    if (judge(board) != "") {
      printBoard(board);
      std::cout << "勝者は: " << judge(board) << std::endl;
      return;
    }
  }
  printBoard(board);
  std::cout << "引き分け" << std::endl;
}

bool retry() {
  char choice;
  std::cout << "もう一度プレイしますか？(y/n): ";
  std::cin >> choice;
  if (choice == 'y' || choice == 'Y') {
    return true;
  } else {
    std::cout << "ゲームを終了します。" << std::endl;
    return false;
  }
}

void printBoard(std::vector<std::string> board) {
  for (int i = 0; i < 9; i++) {
    std::cout << board[i] << " " << " ";
    if (i % 3 != 2) {
      std::cout << "|";
    } else {
      std::cout << std::endl;
      if (i != 8) {
        std::cout << "---------" << std::endl;
      }
    }
  }
}
