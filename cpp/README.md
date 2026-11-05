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
| make | ビルド | `sudo pacman -S --needed make` |
| GoogleTest | テスト | `sudo pacman -S --needed gtest` |

対応環境は Linux / macOS (Windows は WSL)。キー入力に POSIX の `termios` を使っているため。

## 遊び方

```
make game
./game
```

| キー | 動作 |
|---|---|
| ↑ ↓ ← → | カーソルを動かす |
| Enter / スペース | カーソルのマスに置く (埋まっているマスには置けない) |
| q | ゲームを中断する |

- 最初に中央に o が置かれた状態から始まり、x から交互に置く。
- 縦・横・斜めのどれかに 3 つ揃えたら勝ち。盤面が埋まったら引き分け。
- 終わると「もう一度プレイしますか？(y/n)」と聞かれる。

## テスト

```
make test
```

GoogleTest で `judge` (勝敗の判定) をテストする。テストの方針は [docs/test-spec.md](docs/test-spec.md) にまとめている。

## ファイル構成

| ファイル | 中身 |
|---|---|
| `main.cpp` | `main`。ゲームを繰り返す |
| `board.h` / `board.cpp` | 盤面の表示、勝敗の判定、ゲームの進行 |
| `key.h` / `key.cpp` | 矢印キーでマスを選ぶ (`selectCell`) |
| `board_test.cpp` | `judge` のテスト |
| `Makefile` | ビルドとテストのコマンド |
| `docs/test-spec.md` | テスト仕様書 |

## その他のコマンド

```
make        # ゲームとテストを両方ビルド
make clean  # ビルドしたファイルを消す
```
