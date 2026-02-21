# Chess Move Validator in C++ (OOP, rules checking)

## Overview

This C++ project validates chess moves using object-oriented programming principles. It checks **whether each move is legal** according to standard chess rules for each piece: pawns (with capture and partial en passant), knights, bishops, rooks, queens, and kings.

> ⚠️ **Note:** This is a **move validator**, **not a full chess game**. Each move is checked **independently** on the initial board. The board state **does not update** after a move, so moves are **not sequentially applied**.

---

## Features

* **Object-Oriented Design**

  * Base class: `Piece`
  * Derived classes: `King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`
  * Polymorphic `moveable` method to validate moves

* **Chess Rules Implemented**

  * Legal moves for all pieces
  * Pawn captures (including diagonal and partial en passant)
  * Path checking for rooks, bishops, and queens

* **File-Based I/O**

  * Reads initial piece positions and moves from `input.txt`
  * Outputs results (`YES`, `NO`, `TAKE`) to `output.txt`

* **Clean and Modular Code**

  * Separation between `Board` and `Piece` logic
  * Easy to extend for additional rules or game logic

---

## Input/Output Format

**Input (`input.txt`):**

```
n            # number of pieces
<Piece info> x n
m            # number of moves to check
<Move info> x m
```

* Piece info: `<Color><Type><Position>`

  * Color: `W` or `B`
  * Type: `K`, `Q`, `R`, `B`, `N`, `P`
  * Position: board coordinate (e.g., `A1`, `E5`)
* Move info: start and end position concatenated (e.g., `A2A4`)

**Output (`output.txt`):**

* `"YES"` → legal move to empty square
* `"NO"` → illegal move
* `"TAKE"` → move captures an opponent's piece

---

## Sample Input/Output

**input.txt**

```
2
WP A2
BP B7
3
A2A3
B7B6
A2A4
```

**output.txt**

```
YES
YES
NO
```

> These sample files show how to test the project quickly.

---

## How to Compile and Run

Using g++:

```bash
g++ -std=c++17 main.cpp -o ChessValidator
./ChessValidator
```

Make sure `input.txt` is in the same folder. Output will be written to `output.txt`.

---

## Notes / Limitations

* Moves are **checked independently**, without updating the board after each move
* En passant is **partially implemented**
* Does **not** handle:

  * Turn-based play (white/black)
  * Check or checkmate
  * Pawn promotion
* Uses raw pointers (`Piece*`) instead of smart pointers

---

## Potential Improvements

* Apply moves sequentially to update board state
* Fully implement en passant and pawn promotion
* Add turn logic and check/checkmate detection
* Replace raw pointers with `unique_ptr` for memory safety
* Add a text-based or GUI interface for interactive play

---

## Why It’s Useful for a Resume

* Shows **OOP and polymorphism skills** in C++
* Demonstrates ability to **implement complex game logic**
* Clean, modular, and **easy to extend** code
* Works with file input/output — practical for real applications