## 📦 Project Overview: Boxed In - A Sokoban Clone in C

This repository contains **"Boxed In"**, a terminal-based implementation of the classic warehouse puzzle game **Sokoban** ("warehouse keeper"), written entirely in C.

The objective is simple: push all the boxes onto their designated storage targets. The challenge, however, lies in the game's core mechanic:

> **You can only push boxes, never pull them.**

This single constraint transforms the game into a deep strategic puzzle, where every move must be carefully considered to avoid trapping boxes and creating unwinnable scenarios.
### Core Features
- **2D Grid Environment:** The game board is managed using a 2D `char` array, loaded from level files.
- **Game Logic in C:** All mechanics, including player movement, box pushing, and collision detection, are implemented using  C programming language.
- **State Management:** The program tracks the positions of the player and all boxes to check for the win-condition.
