# MY Mastermind
Welcome to my mastermind.

# Describtion
my_mastermind is a simple C program that implements the classic game of Mastermind. The game generates a secret code of four digits (0-9), and the player has to guess the code within a limited number of rounds. After each guess, the game provides feedback on the correctness of the guess.

# Instalation
You can download the source code files directly from this repository. Follow the steps below to clone the repository to your local machine:

## Prerequisites

Before you begin, ensure you have the following installed on your system:

- Git: You can download and install Git from [`here`](https://git-scm.com/).

## Cloning the Repository

1. Clone the Repository: Open a terminal window and navigate to the directory where you want to store the project.

```
cd /path/to/desired/location
```
2. Clone the Repository: Run the following command to clone the repository to your local machine:
```
git clone https://github.com/your-username/your-repository.git
```
Replace `https://github.com/your-username/your-repository.git` with the URL of your GitHub repository.

# Usage

To compile the my_mastermind program, ensure you have a C compiler installed on your system (e.g., gcc). Then, navigate to the project directory containing the source code and the Makefile and run the following command:
```
make
```
This command will compile the source files and generate an executable named my_mastermind.

After compiling the program, you can run it from the terminal. The program supports command-line arguments to specify options such as the secret code and the number of rounds.

Here is the syntax to run the program:
```
./my_mastermind [-c <code>] [-t <rounds>]
```

- -c `<code>:` Optional argument to specify the secret code. If not provided, a random code will be generated.
- -t `<rounds>:` Optional argument to specify the number of rounds to play. If not provided, the default is 10 rounds.

# The Core Team

- Safarboyef Muhammad