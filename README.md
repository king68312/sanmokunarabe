# sanmokunarabe

English | [日本語](README.ja.md)

A terminal tic-tac-toe game, implemented in several languages and architectures as a learning project.

```
矢印キーで移動(q で終了)
x  |   |
-----------
   |o  |
-----------
   |   |
```

The goal is to write the same game in different languages and compare how each one shapes the design.

## Status

| Language | Architecture | Status | Location |
|---|---|---|---|
| C++ | MVC | Playable (tests: WIP) | [cpp/](cpp/) |
| Rust | — | TODO | — |
| Elm | The Elm Architecture | TODO | — |
| Haskell | — | TODO | — |

## TODO

This project is a work in progress.

- [x] C++: playable game with an MVC structure
- [ ] C++: tests for the Model (`judge`, cursor movement, turn order) — in progress
- [ ] Rust port
- [ ] Elm port
- [ ] Haskell port

## Rules

- The game starts with an `o` already placed in the center; `x` moves first and players alternate.
- Three in a row (horizontal, vertical, or diagonal) wins. A full board with no line is a draw.
- Move the cursor with the arrow keys, place a mark with Enter or Space, and quit with `q`.

The detailed rules and the testing policy are in [docs/test-spec.md](docs/test-spec.md) (Japanese). Every implementation follows that spec.

## Design principles

- **The rules (Model) never touch the screen or the keyboard.** All input and output live in the outer layers (View / Controller).
- Because of that, the rules can be built and tested on their own.
- When porting to another language, the rules can be translated almost as-is; only the input/output layer is rewritten in that language's style.

## Directory layout

```
sanmokunarabe/
├── README.md        this file (English)
├── README.ja.md     Japanese version
├── docs/
│   └── test-spec.md rules and test spec, shared by all languages
└── cpp/             C++ version (build instructions in cpp/README.md)
```
