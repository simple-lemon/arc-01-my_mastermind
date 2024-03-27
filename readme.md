# Welcome to my_mastermind

## Task
Your task is to implement the game "Mastermind" in C programming language. Mastermind is a code-breaking game where one player (the codebreaker) tries to guess the secret code chosen by the other player (the codemaker). The codebreaker makes a series of guesses, and after each guess, the codemaker provides feedback in terms of "well-placed" and "misplaced" pieces.

## Description
The provided code contains functions to implement the game logic, such as generating a random secret code, evaluating guesses, checking input validity, and handling game flow. You need to fill in the missing parts, complete the implementation, and ensure that the game runs smoothly.

## Installation
To install the game, follow these steps:
1. Copy the provided C code into a file named `my_mastermind.c`.
2. Compile the code using a C compiler. For example, you can use GCC with the following command:
   ```
   gcc -o my_mastermind my_mastermind.c
   ```
3. Run the compiled executable:
   ```
   ./my_mastermind
   ```

## Usage
Once the game is running, follow the on-screen prompts to play Mastermind. You can also provide command-line arguments to specify the number of attempts allowed or provide a custom secret code. Here are the available command-line options:
- `-t <attempts>`: Set the number of attempts allowed (default is 10).
- `-c <code>`: Provide a custom secret code to be guessed by the player.

Example usage:
```
./my_mastermind -t 12 -c 1234
```

This would start the game with 12 attempts to guess the code "1234".

Enjoy playing Mastermind!