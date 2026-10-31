#pragma once

#include <string>
#include <vector>

int selectCell(const std::vector<std::string>& board);

enum class Key { kUp, kDown, kLeft, kRight, kEnter, kQuit, kOther };

struct Position {
  int row;
  int col;
};
