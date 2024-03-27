# arc-01-my_mastermind

This C program implements a simple version of the Mastermind game, a classic code-breaking game where players attempt to guess a secret code within a limited number of attempts. The secret code is a sequence of digits, and the player receives feedback after each guess, helping them refine their subsequent guesses.

## How to Play

1. **Objective**: The player's goal is to guess the secret code within a limited number of attempts.

2. **The Secret Code**: The secret code is a sequence of four digits. Each digit can range from 0 to 8. Digits cannot repeat within the code.

3. **Making Guesses**: The player makes guesses by entering a sequence of four digits. After each guess, the game provides feedback:
   - Number of well-placed digits: Indicates the number of correct digits in the correct positions.
   - Number of misplaced digits: Indicates the number of correct digits in incorrect positions.

4. **Winning the Game**: The player wins the game by correctly guessing all four digits in the correct positions within the given attempts.

5. **Game Over**: If the player exhausts all attempts without correctly guessing the code, the game ends.

## Command-line Arguments

The program accepts the following command-line arguments to customize the gameplay:

- `-t <attempts>`: Sets the maximum number of attempts allowed. If not provided, the default is 10.
- `-c <code>`: Sets the secret code manually. If not provided, the program generates a random code.

Example usage:
```bash
./mastermind -t 12 -c 1234
```

# Functions Overview
- `generate_random_code: Generates a random secret code.`
- `is_incorrect_input: Checks if the user input is valid.`
- `count_well_placed: Counts the number of well-placed digits in the guess.`
- `count_missed_placed: Counts the number of correctly guessed but misplaced digits.`
- `print_congratulations_message: Prints a congratulatory message upon winning.` 
- `print_attempt_message: Prints the current round message.`
- `read_user_input: Reads user input from the console.`
- `process_user_input: Processes the user input.`
- `print_well_and_missed: Prints the number of well-placed and missed-placed digits.`
- `play_game: Initiates the game loop.`
- `Other utility functions for command-line argument parsing, string manipulation, and memory management.`


# Dependencies

The program uses standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, and `time.h`.

# Compilation

To compile the program, use a C compiler such as `gcc` :

```
gcc mastermind.c -o mastermind
```

# Usage

Run the compiled executable with optional command-line arguments to customize the gameplay.

# Contributions

Contributions and suggestions are welcome. Feel free to fork this repository, make enhancements, and submit pull requests.

