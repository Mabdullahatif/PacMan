# Pacman Game

This repository contains the code for a simple `Pacman` game implemented in C++. The game uses the "mygraphics.h" library for graphics rendering.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Game Overview](#game-overview)
    - [Characters](#characters)
    - [Gameplay Elements](#gameplay-elements)
    - [Game Over](#game-over)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Game Logic](#game-logic)
- [Contributing](#contributing)
- [Intial Contributor](#initial-contributor)

## Introduction
This project is a classic Pacman game implemented in C++. The game uses the "mygraphics.h" library to handle graphics rendering. The main objective of the game is to control the Pacman character and eat all the dots while avoiding the ghosts.

## Features
- Classic Pacman gameplay with simple and intuitive controls.
- Smart enemy with random chasers and prowlers for challenging gameplay.
- Score tracking and display to keep track of the player's progress.
- Game over and victory messages to provide feedback to the player.

## Game Overview
The game takes place in a maze-like environment, where Pacman, the player's character, must navigate through the maze to eat all the dots. As Pacman moves, the ghosts attempt to chase and catch him. The player must strategize to avoid the ghosts while trying to collect as many dots as possible to score points.

### Characters
1. **Pacman**: The main protagonist of the game, represented by a yellow circle. The player controls Pacman to move around the maze and eat the dots. Pacman can move in four directions: up, down, left, and right.
2. **Ghosts**: There are two types of ghosts:
   - **Random Chasers**: These ghosts move randomly throughout the maze, making them unpredictable and challenging to avoid.
   - **Prowlers**: Prowlers are smarter ghosts that actively chase Pacman. They attempt to predict his movements and cut him off, making them more challenging opponents.

### Gameplay Elements
- **Dots**: Scattered throughout the maze, Pacman can eat these dots to score points. The player's score increases with each dot eaten.
- **Lives**: The player starts with a certain number of lives (usually three). If Pacman collides with a ghost, he loses a life. The game continues until the player runs out of lives.
- **Score**: The player's score increases as Pacman eats dots. The objective is to achieve the highest score possible.
- ### **Main Screen**
- ![pacman1](https://github.com/avcton/PacMan/assets/113658337/d2f8a22e-381e-4b14-bb17-aab69555b5d5)


### Game Over
The game ends under the following conditions:
- **Win Condition**: The player wins the game when Pacman successfully eats all the dots in the maze, achieving a complete clear of the board.
  ![pacman3](https://github.com/avcton/PacMan/assets/113658337/82c92501-9c90-4ea5-88ff-2daf6139c749)


- **Lose Condition**: The player loses the game when Pacman loses all of his lives by colliding with ghosts. Upon losing all lives, the player receives a game-over message, and the game can be restarted.
  ![pacman2](https://github.com/avcton/PacMan/assets/113658337/06217f60-fe99-40b7-a788-99a63a452424)



## Installation
To run the game, you need a C++ compiler that supports the "mygraphics.h" library.

## How to Play
1. Clone the repository to your local machine or simply download the .zip file.
2. Compile the source code using a C++ compiler.
3. Run the executable to start the game.
4. Use the following controls to move Pacman:
   - 'd' - Move right
   - 'a' - Move left
   - 'w' - Move up
   - 's' - Move down
   - 'q' - Quit the game
   - 'c'  - Cheat Code for instant escape

## Game Logic
The main game loop is implemented in the `main` function, which controls the flow of the game. It uses classes for `Player`, `Board`, and `Enemy`, representing the main character, the game board, and the ghosts, respectively.

The game loop does the following:
1. Initializes the game state and objects.
2. Draws the game board and maze.
3. Checks for player input to move Pacman.
4. Updates the game state based on player actions and enemy movements.
5. Checks for collisions with dots and ghosts.
6. Ends the game when the player wins or loses.

The `mygraphics.h` library is used for graphics rendering in the console.

## Contributing

Contributions to this project are welcome! If you have any suggestions, bug fixes, or new features to add, please open an issue or submit a pull request.

## Initial Contributor

So far, all the work in this repository is purely done by me and [Avcton](https://github.com/avcton)

Happy gaming! 🎮
