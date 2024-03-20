## Task
The challenge lies in implementing the game logic, including generating a random secret code, receiving and validating user input, evaluating the guess, and providing feedback to the player.

## Description
I set up a C project with necessary libraries (stdio.h, stdlib.h, string.h, time.h) and defined constants for the game (max_attempts, code_length, colors).I created many functions like makeSecretCode to generate a random secret code using the rand() function. I stored the input in a buffer (guess) and null-terminated it to form a string.I implemented the evaluateGuess function to compare the user's guess with the secret code and calculate the number of well-placed and misplaced pieces.I used a for loop to iterate through the game rounds (attempts) and break the loop if the user guesses the code correctly or runs out of attempts.



## Installation
git clone https://github.com/yourusername/my_mastermind.git
cd mastermind
gcc -o mastermind my_mastermind.c

## Usage
At the beginning of the game, a secret code of a specified length is generated randomly. The code is made up of digits from 0 to 8.The player is given a certain number of attempts to guess the secret code. The number of attempts is specified by the player or defaults to 10.The game consists of several rounds, each representing a player's guess. The player enters a guess for the secret code.After each guess, the program evaluates the guess and provides feedback to the player. The game continues until the player correctly guesses the secret code or runs out of attempts. If the player guesses the code correctly, a congratulatory message is displayed. Otherwise, the game reveals the secret code and ends.
