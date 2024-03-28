## Welcome to My Mastermind

Welcome to my implementation of the classic game Mastermind! In this game, your task is to guess a secret code within a limited number of attempts. The code consists of a sequence of digits, and you need to deduce both the correct digits and their positions.

## Task

Your task is to guess the secret code within a certain number of attempts. After each guess, you will receive feedback on how many digits you've guessed correctly and how many are in the correct position.

## Description

This Mastermind game is implemented in C and can be compiled and run on any system with a C compiler. The game allows you to specify the number of attempts you want to make and even provides an option to set the secret code manually for testing purposes. If the code is not specified, a random code will be generated for you.

## Installation

To install and play the game, follow these steps:

1. Clone the repository to your local machine:


shell


   git clone <repository_url>


2. Navigate to the directory containing the game files.

3. Compile the source code using a C compiler. For example, using gcc:


shell


   gcc -o mastermind mastermind.c


4. Run the compiled executable:


shell


   ./mastermind


## Usage

Once you've compiled and run the game, follow these steps to play:

1. You will be prompted to enter your guess.

2. Enter a sequence of four digits. Each digit should be between 0 and 8, and no digit should be repeated within the sequence.

3. After each guess, the game will provide feedback indicating how many digits you've guessed correctly and how many are in the correct position.

4. Continue guessing until you either correctly guess the entire code or run out of attempts.

5. If you correctly guess the code, you win! Otherwise, the game will reveal the secret code.

Start the game:

    ./mastermind [-c secret_code] [-t attempts]
Optional command line arguments:

-c: Set the secret code manually. If not provided, a random code will be generated.
-t: Set the number of attempts. Default is 10.

Gameplay
  Follow the on-screen prompts to make guesses. The game provides feedback on each guess, and you can enter "stop" at any time to end the game.
Enjoy playing Mastermind!