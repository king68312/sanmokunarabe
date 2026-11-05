#pragma once

#include <string>
#include <vector>

#include "model.h"

int selectCell(const std::vector<std::string>& board);

// main.cpp
bool playGame();
bool retry();

void enableRawMode();
void disableRawMode();

Key readKey();
Position movePosition(Position pos, Key key);
int selectCell(const std::vector<std::string>& board);
