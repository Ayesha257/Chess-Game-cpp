# Chess Game in C++ (OOP Based)

This is a console-based Chess game developed in C++ using Object-Oriented Programming (OOP) principles. The project implements a fully functional chessboard with standard rules, turn-based gameplay, and move validation for all chess pieces.

---

## Project Overview

The game simulates a classic two-player chess experience where each player takes turns to move their pieces according to standard chess rules. The system ensures legal move validation, board state updates, and proper turn management.

This project focuses on applying OOP concepts such as encapsulation, inheritance, and polymorphism to design a modular and maintainable chess system.

---

## Features

### Gameplay

- 2-player turn-based chess system
- Standard 8x8 chessboard representation
- White vs Black player turns
- Move input system via console

### Chess Logic

- Legal move validation for all pieces:
  - Pawn
  - Rook
  - Knight
  - Bishop
  - Queen
  - King
- Capture system for opponent pieces
- Basic rule enforcement for valid moves

### Game System

- Turn switching mechanism
- Board state updates after every move
- Invalid move detection and handling
- Continuous gameplay loop until game ends

---

## OOP Concepts Used

- Encapsulation: Piece and board data is managed within classes
- Inheritance: Different chess pieces derived from a base Piece class
- Polymorphism: Overridden movement rules for each piece type
- Abstraction: Game logic hidden behind class interfaces

---

## Project Structure

```text
ChessGame/
│
├── main.cpp
├── Board.cpp / Board.h
├── Pieces.cpp / Pieces.h
├── Game.cpp / Game.h
└── README.md
How to Run
1. Compile the Code

Using g++:

g++ main.cpp Board.cpp Pieces.cpp Game.cpp -o ChessGame
2. Run the Game
./ChessGame
How to Play
The game runs in the console.
Players enter moves in coordinate format (example format depends on implementation, such as e2 e4).
The system checks if the move is valid.
If valid, the piece is moved and the turn switches.
If invalid, the player is asked to try again.
Learning Outcomes

This project helps in understanding:

Object-Oriented Programming in C++
Class design and modular programming
Game logic implementation
Move validation algorithms
Board representation techniques
Turn-based system design
Future Improvements
Add check and checkmate detection
Add castling and en passant rules
Add pawn promotion
Add AI opponent (minimax algorithm)
Add GUI version using SFML or Qt
Add move history and undo feature
Add save/load game functionality

Authors:
Ayesha Amer
Rida Fatima Tanvir
```
