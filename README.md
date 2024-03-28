# My Mastermind

## Overview
My Mastermind is a console-based implementation of the classic game, Mastermind. In this game, a secret code is generated, and the player’s goal is to guess this code within a certain number of attempts. The secret code is composed of 4 distinct digits, ranging from 0 to 8. After each guess, the game provides feedback to the player in the form of the number of well-placed and misplaced digits.

## Usage
The game can be customized via command-line arguments:

- `-c`: Allows you to set a custom secret code.
- `-t`: Allows you to set a custom number of attempts.

By default, the secret code is randomly generated and the number of attempts is set to 10.

Example usage:

`./my_mastermind -c "0123" -t 8`

## Game Rules
The game begins with the generation of a secret code. The player then makes a series of guesses, attempting to determine the secret code. After each guess, the game provides two pieces of feedback:

- The number of well-placed digits: These are digits that are both correct and in the correct position.
- The number of misplaced digits: These are digits that are correct but in the wrong position.

The game continues until the player correctly guesses the code or runs out of attempts.

## Installation
No installation is necessary to play the game. Simply compile the source code and run the resulting executable.

## License
This project is not currently licensed under MIT or any other license. Please use responsibly and respect the rights of the creator.
