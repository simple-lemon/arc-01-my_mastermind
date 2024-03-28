#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *generate_random_code() {
    srand(time(NULL));
    char *code = (char *)malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; i++) {
        code[i] = rand() % 10 + '0'; 
        for (int j = 0; j < i; j++) {
            if (code[i] == code[j]) {
                i--;
                break;
            }
        }
    }
    code[4] = '\0';
    return code;
}

int check_input_validity(char *input) {
    if (strlen(input) != 4) {
        printf("Input must be 4 digits!\n");
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Input must contain only digits!\n");
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                printf("Digits must be unique!\n");
                return 0;
            }
        }
    }

    return 1;
}

void evaluate_guess(char *code, char *guess, int *good, int *unitized) {
    *good = 0;
    *unitized = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i]) {
            (*good)++;
        } else {
            for (int j = 0; j < 4; j++) {
                if (guess[i] == code[j]) {
                    (*unitized)++;
                    break;
                }
            }
        }
    }
}

char *get_user_guess() {
    char *guess = (char *)malloc(sizeof(char) * 5);
    printf("Enter your guess (4 digits): ");
    scanf("%s", guess);
    return guess;
}

void play_my_mastermind(int attempts, char *code) {
    printf("Welcome to My Mastermind!\n");
    printf("Try to guess the 4-digit secret code.\n");

    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i + 1);
        char *guess;
        do {
            guess = get_user_guess();
        } while (!check_input_validity(guess));

        int good, unitized;
        evaluate_guess(code, guess, &good, &unitized);
        free(guess);

        if (good == 4) {
            printf("Congratulations! You cracked the code!\n");
            return;
        } else {
            printf("Correctly placed digits: %d\n", good);
            printf("Misplaced digits: %d\n", unitized);
        }
    }

    printf("Game over! The secret code was: %s\n", code);
}

int main() {
    int attempts;
    printf("Enter the number of attempts: ");
    scanf("%d", &attempts);

    char *code = generate_random_code();
    play_my_mastermind(attempts, code);
    free(code);

    return 0;
}
