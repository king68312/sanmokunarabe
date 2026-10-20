#include "board.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

// 何も置かれていない盤面では、揃っているラインがない
TEST(JudgeTest, ReturnsEmptyForEmptyBoard) {
  std::vector<std::string> board(9, " ");
  EXPECT_EQ(judge(board), "");
}

// 一番上の行が x で揃っていれば "x" を返す
TEST(JudgeTest, ReturnsXWhenTopRowIsX) {
  // clang-format off
  std::vector<std::string> board = {"x", "x", "x",
                                    " ", "o", " ",
                                    "o", " ", " "};
  // clang-format on
  EXPECT_EQ(judge(board), "x");
}

// 真ん中の列が o で揃っていれば "o" を返す
TEST(JudgeTest, ReturnsOWhenMiddleColumnIsO) {
  // clang-format off
  std::vector<std::string> board = {"x", "o", " ",
                                    " ", "o", "x",
                                    "x", "o", " "};
  // clang-format on
  EXPECT_EQ(judge(board), "o");
}

}  // namespace
