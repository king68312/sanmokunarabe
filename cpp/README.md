# 三目並べ

ターミナルで遊ぶ三目並べ (C++)。矢印キーでマスを選んで、x と o を交互に置く。

```
矢印キーで移動(q で終了)
x  |   |
---------
   |o  |
---------
   |   |
```

## 必要なもの

| もの | 用途 | Arch Linux でのインストール |
|---|---|---|
| g++ (C++17 対応) | ビルド | `sudo pacman -S --needed gcc` |
| GoogleTest | テスト | `sudo pacman -S --needed gtest` |

対応環境は Linux / macOS (Windows は WSL)。キー入力に POSIX の `termios` を使っているため。

## 遊び方

`cpp/` の中で次を実行する。

```
g++ -std=c++17 -Wall -Wextra -Wmissing-declarations main.cpp model.cpp view.cpp controller.cpp -o game
./game
```

| キー | 動作 |
|---|---|
| ↑ ↓ ← → | カーソルを動かす |
| Enter / スペース | カーソルのマスに置く (埋まっているマスには置けない) |
| q | ゲームをやめる (そのまま終了する) |

- 最初に中央に o が置かれた状態から始まり、x から交互に置く。
- 縦・横・斜めのどれかに 3 つ揃えたら勝ち。盤面が埋まったら引き分け。
- 勝負がつくと結果の盤面が表示され、「もう一度プレイしますか？(y/n)」と聞かれる。

## テスト

`cpp/` の中で次を実行する。テストはルール (`model.cpp`) だけとリンクする。

```
g++ -std=c++17 -Wall -Wextra board_test.cpp model.cpp -lgtest -lgtest_main -pthread -o board_test
./board_test
```

GoogleTest で `judge` (勝敗の判定) をテストする。テストの方針は [docs/test-spec.md](../docs/test-spec.md) にまとめている。

## 構成 (MVC)

役割ごとに Model / View / Controller の 3 つに分けている。

```
main.cpp ──→ controller ──→ model
                 │            ↑
                 └─→ view ────┘

model は画面もキーボードも使わない (テストできるように)
```

| ファイル | 役割 | 中身 |
|---|---|---|
| `model.h` / `model.cpp` | Model: データとルール | `judge` (勝敗の判定), `toIndex`, `Position` |
| `view.h` / `view.cpp` | View: 画面に描く | `printBoard`, `showCursor`, `saveOrigin`, `backToOrigin` |
| `controller.h` / `controller.cpp` | Controller: 入力とゲームの進行 | `enableRawMode`, `disableRawMode`, `readKey`, `movePosition`, `selectCell`, `playGame`, `retry` |
| `main.cpp` | 入口 | ゲームを繰り返す。`q` でやめたらそのまま終了 |
| `board_test.cpp` | テスト | `judge` のテスト |
| `../docs/test-spec.md` | 仕様 | テスト仕様書 (全言語で共有) |
