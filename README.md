# Mayan Number Game

The **Mayan Number Game** is a C++ console application that challenges you to match decimal numbers with their corresponding Mayan numeral representations. This interactive game not only tests your knowledge of numbers but also introduces you to the fascinating Mayan numeral system.

---

## Features

- **Mayan Numerals Representation:**  
  Utilizes Unicode characters to visually represent Mayan bars and dots.
  
- **Randomized Rounds:**  
  Generates random decimal numbers and multiple answer choices each round.

- **Interactive Gameplay:**  
  Provides immediate feedback on your guesses, showing the correct Mayan numeral representation if you err.

- **Educational:**  
  Learn about the Mayan numeral system through an engaging, game-based approach.

---

## How It Works

1. **Game Setup:**
   - A sample Mayan numeral (for the number 2,072,025) is displayed on launch.
   - The user is prompted to enter a maximum number (must be at least 10) that sets the range for the guessing game.

2. **Gameplay:**
   - A random decimal number within the specified range is generated.
   - The program converts the decimal number to its Mayan numeral representation by decomposing it using powers of 20.
   - Three answer choices are generated: one correct and two incorrect options.
   - You choose the Mayan numeral that corresponds to the given decimal number.
   - The game provides feedback on your selection, displaying the correct Mayan numeral if you make an incorrect guess.

3. **Rounds:**
   - The game is structured to allow up to 10 rounds of play.
   - After each round, you have the option to continue or exit the game.

---

## Getting Started

### Prerequisites

- **C++ Compiler:**  
  C++ compiler (e.g., g++, clang++).

### Compiling the Game

```bash
g++ -o mayan_game main.cpp
