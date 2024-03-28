# arc-01-my_mastermind

This simple C program implements a Mastermind game where the user tries to guess a secret 4-digit code. The game provides feedback to the user after each guess, indicating the number of correct digits in the correct position and the number of correct digits in the wrong position.

## Features

- **Random Code Generation:** The secret code is randomly generated at the start of each game. The code consists of 4 unique digits between 0 and 9.
  
- **User Input Validation:** The program ensures that user input for guessing the code is valid. Invalid inputs such as non-numeric characters, inputs of incorrect length, or repeated digits are rejected with appropriate error messages.

- **Feedback Mechanism:** After each guess, the program provides feedback to the user indicating the number of digits correctly guessed and placed in the correct position, as well as the number of correct digits guessed but placed in the wrong position.

- **Limited Attempts:** The game allows the user a limited number of attempts to guess the code. If the user fails to guess the code within the specified number of attempts, the game ends.

## Usage

1. **Compilation and Execution:**
   - Use the `make` command in the terminal to compile the code.
   - Run the generated executable using the `./mastermind` command in the terminal.
   - Upon starting the program, the user is prompted to enter the number of attempts they want for the game.

2. **Gameplay:**
   - The user is prompted to enter a 4-digit guess.
   - After each guess, the program provides feedback on the correctness of the guess.
   - The game continues until the user correctly guesses the 4-digit secret code or exhausts all attempts.

3. **Winning and Losing:**
   - If the user correctly guesses the secret code within the specified number of attempts, they win the game.
   - If the user fails to guess the code within the given attempts, they lose the game, and the secret code is revealed.

## Development

- **Language:** The code is written in the C programming language.
- **Dependencies:** No external dependencies are required to compile or run the program.
- **Modularity:** The code is structured into separate functions for code generation, input validation, guess evaluation, and gameplay.
- **Memory Management:** Dynamic memory allocation is used for generating the secret code and capturing user guesses. Memory is properly deallocated to prevent memory leaks.

## License

This code is not licensed under any license, and its usage, modification, and distribution are unrestricted.

