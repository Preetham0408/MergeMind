# MergeMind — 2048 Number-Merging Puzzle

MergeMind is a terminal-based implementation of the classic 2048 number-merging puzzle, developed in C++ using Object-Oriented Programming (OOP) concepts.

The objective is to move numbered tiles across a 4 × 4 grid, merge tiles with equal values, increase the score, and create the **2048 tile**.

## Features

- Four-direction movement: Up, Down, Left, and Right
- Tile merging and score tracking
- Random tile generation
- Win and game-over detection
- Save and load game progress
- Restart and start a new game
- Aligned terminal board display using output operator overloading

## Technologies Used

- **Language:** C++17
- **Compiler:** GCC / MinGW-w64
- **Libraries:** C++ Standard Library (STL)
- **Concepts:** Object-Oriented Programming
- **File Handling:** C++ file streams
- **Interface:** Console / terminal
- **Future Enhancement:** SFML graphical interface

## Project Structure

```text
MergeMind/
├── header/
│   ├── Game.h
│   ├── GameBoard.h
│   ├── SaveManager.h
│   └── ScoreManager.h
├── Game.cpp
├── GameBoard.cpp
├── SaveManager.cpp
├── ScoreManager.cpp
├── main.cpp
├── .gitignore
├── MergeMind
├── mergemind_save.txt
└── README.md
```

- **`main.cpp`** — Application entry point.
- **`Game.cpp`** — Controls the game loop and user interaction.
- **`GameBoard.cpp`** — Implements board initialization, movement, merging, and game-state checks.
- **`ScoreManager.cpp`** — Manages the player's score.
- **`SaveManager.cpp`** — Handles saving and loading game progress.
- **`header/`** — Contains the corresponding header files and class declarations.

The `MergeMind` executable and `mergemind_save.txt` are generated or runtime files, not source files.

## Prerequisites

- GCC with C++17 support
- VS Code or another C++ development environment
- A terminal opened in the project root directory

## Build and Run

### Linux / WSL

Compile the project from the root directory:

```bash
g++ GameBoard.cpp Game.cpp ScoreManager.cpp SaveManager.cpp main.cpp -o MergeMind
```

Run the game:

```bash
./MergeMind
```

### Windows with MinGW-w64

Compile:

```powershell
g++ GameBoard.cpp Game.cpp ScoreManager.cpp SaveManager.cpp main.cpp -o MergeMind.exe
```

Run:

```powershell
.\MergeMind.exe
```

**Note:** These short commands assume your source files remain in the project root and your header includes correctly reference the `header/` directory, for example:

```cpp
#include "header/Game.h"
```

Use the corresponding header name in each source file.

## How to Play

Launch the executable and follow the displayed controls.

| Key | Action |
|---|---|
| `W` | Move Up |
| `S` | Move Down |
| `A` | Move Left |
| `D` | Move Right |
| `P` | Save Game |
| `L` | Load Game |
| `N` | Start a New Game |
| `Q` | Quit |

The objective is to combine equal-valued tiles until a tile reaches 2048. The score increases when tiles merge.

## Object-Oriented Programming Concepts

MergeMind organizes the implementation into separate classes:

- **Game:** Coordinates the game loop and user input.
- **GameBoard:** Manages the board and game mechanics.
- **ScoreManager:** Maintains the score.
- **SaveManager:** Handles persistent game data.

The project demonstrates class design, encapsulation, abstraction, composition, output operator overloading, and file handling where implemented in the source code.

## Future Enhancements

- Develop a graphical interface using SFML.
- Add tile animations and visual effects.
- Improve input handling and error messages.
- Add automated tests for game mechanics.

## License

This project is intended for educational purposes. Add an appropriate license if you plan to distribute or reuse the code publicly.
