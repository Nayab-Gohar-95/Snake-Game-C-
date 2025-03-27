# Snake Game (C++)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Game Mechanics](#game-mechanics)
- [Technologies Used](#technologies-used)
- [Project Structure](#project-structure)
- [Setup and Installation](#setup-and-installation)
- [How to Play](#how-to-play)
- [Future Improvements](#future-improvements)

## Introduction
This is a **classic Snake Game** implemented in **C++**. The game features basic snake mechanics, score tracking, and sound effects for enhanced gameplay.

## Features
- Moveable snake that grows upon eating food.
- Real-time score tracking.
- Game-over detection when the snake collides with itself or walls.
- Sound effects for food collection, game start, and game over.

## Game Mechanics
- The player controls a snake moving around the screen.
- Eating food increases the snake's length and score.
- The game ends when the snake collides with the wall or itself.

## Technologies Used
- **C++** (Game Logic)
- **Windows.h** (for handling graphics and system functions)
- **Audio Files** (WAV format for game sounds)

## Project Structure
```
.
├── Snake_Game.cpp       # Main game source code
├── coin.wav             # Sound effect when food is eaten
├── game_over.wav        # Sound effect when the game ends
├── Start.wav            # Sound effect when the game starts
├── README.md            # Project documentation
```

## Setup and Installation

### **Compiling the Game**
1. **Using g++ (MinGW on Windows)**:
   ```sh
   g++ Snake_Game.cpp -o Snake_Game.exe -lwinmm
   ```
   (The `-lwinmm` flag is required for playing sound on Windows.)

2. **Using Dev-C++**:
   - Open `Snake_Game.cpp` in Dev-C++.
   - Configure `libwinmm.a` in the linker settings.
   - Compile and run the project.

## How to Play
- Use **Arrow Keys (← ↑ → ↓)** to control the snake.
- Eat food (**represented by a symbol**) to grow and increase your score.
- Avoid hitting walls and your own body.
- The game ends when you collide with the wall or yourself.

## Future Improvements
- Implement difficulty levels.
- Add more sound effects and background music.
- Introduce power-ups or bonus items.
- Make the game playable on Linux and MacOS.


