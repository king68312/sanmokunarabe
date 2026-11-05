#pragma once

#include <string>
#include <vector>

#include "model.h"

int selectCell(const std::vector<std::string>& board);

void saveOrigin();
void backToOrigin();
void showCursor(Position pos);
void printBoard(const std::vector<std::string>& board);
