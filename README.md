# arc-01-my_mastermind

This C program implements a simple version of the Mastermind game, a classic code-breaking game where players attempt to guess a secret code within a limited number of attempts. In this implementation, the secret code is a sequence of digits, and the player receives feedback after each guess, helping them refine their subsequent guesses.

## About Mastermind

Mastermind is a classic board game invented by Mordecai Meirowitz in 1970. It gained popularity due to its simple yet challenging gameplay. The game requires both logic and deduction skills, making it suitable for players of all ages.

## How to Play

1. **Objective**: The player's goal is to guess the secret code within a limited number of attempts.

2. **The Secret Code**: The secret code is a sequence of digits. In this implementation, the code length is fixed at 4 digits. Each digit can range from 0 to 8. Digits cannot repeat within the code.

3. **Making Guesses**: The player makes guesses by entering a sequence of digits. After each guess, the game provides feedback to help the player refine their next guess.

4. **Feedback**: After each guess, the game provides feedback in two parts:
   - Number of well-placed digits: Indicates the number of correct digits in the correct positions.
   - Number of misplaced digits: Indicates the number of correct digits in incorrect positions.

5. **Gameplay Continues**: The player continues guessing until they correctly guess the entire code or exhaust their allowed attempts.

## Customization Options

The program offers customization options to tailor the gameplay experience:

- **Setting the Secret Code**: Players can set the secret code manually using the `-c <code>` command-line option. The code must adhere to the format rules (4 digits, each ranging from 0 to 8, and no repeating digits).

- **Adjusting the Number of Rounds**: Players can specify the maximum number of rounds allowed using the `-t <rounds>` command-line option.

If customization options are not provided, the program generates a random secret code and sets the default maximum rounds to 10.

## Functions Overview

- `GenerateSecretCode`: Generates a random secret code adhering to the game's rules.
- `CheckValidGuess`: Validates whether a guess is valid according to the game's rules.
- `ReadGuess`: Reads a guess input from the player.
- `CounterPlaces`: Provides feedback on the correctness of a guess by counting well-placed and misplaced digits.
- `UserAttempts`: Manages the main game loop, player interactions, and feedback.

## File Structure

- `mastermind.c`: Contains the source code of the Mastermind game.
- `README.md`: This README file providing detailed information about the game, how to play, customization options, and function overview.

## Dependencies

The program relies on standard C libraries (`stdio.h`, `stdlib.h`, `time.h`, `unistd.h`).

## Contributors

This program was created by [Your Name] ([Your GitHub Profile](https://github.com/maqsudbekov005/)).

## License

Feel free to contribute to or modify this program according to your needs! Your feedback and contributions are appreciated.

## Additional Notes

This implementation aims to provide a basic yet functional version of the Mastermind game. Further enhancements, such as graphical interfaces, additional gameplay modes, or advanced algorithms for generating secret codes, can be explored for more sophisticated versions of the game.