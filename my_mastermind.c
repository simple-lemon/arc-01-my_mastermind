#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

void generateSecretCode(char* secretCode) {
    const char pieces[] = "012345678";
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = pieces[rand() % 9];
    }
    secretCode[CODE_LENGTH] = '\0';
}

int my_strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void my_strncpy(char* dest, const char* src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
}

void evaluateGuess(const char* secretCode, const char* guess, int* wellPlaced, int* misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == secretCode[i]) {
            (*wellPlaced)++;
        } else {
            for (int j = 0; j < CODE_LENGTH; j++) {
                if (i != j && guess[i] == secretCode[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
}

int isValidGuess(const char* guess) {
    if (my_strlen(guess) != CODE_LENGTH) {
        return 0;
    }
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] < '0' || guess[i] > '8') {
            return 0;
        }
        for (int j = i + 1; j < CODE_LENGTH; j++) {
            if (guess[i] == guess[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int my_scanf(char* str) {
    int index = 0;
    char letter;
    write(1, ">", 1);
    while (read(STDIN_FILENO, &letter, 1) > 0) {
        if (letter == '\n' || index == CODE_LENGTH + 1) {
            str[index] = '\0';
            return 1;
        }
        str[index++] = letter;
    }
    if (index == 0) {
        printf("\nCtrl+D pressed. Exiting...\n");
        exit(0);
    }
    return 0;
}

void playGame(const char* secretCode, int maxAttempts) {
    char guess[CODE_LENGTH + 1];
    int attempts = maxAttempts;
    int round = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (attempts > 0) {
        printf("---\nRound %d/%d\n", round, maxAttempts);
        if (!my_scanf(guess)) {
            printf("Wrong input!\n");
            continue;
        }
        if (!isValidGuess(guess)) {
            printf("Wrong input!\n");
            continue;
        }
        int wellPlaced, misplaced;
        evaluateGuess(secretCode, guess, &wellPlaced, &misplaced);
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!");
            return;
        }
        attempts--;
        round++;
    }
    printf("Game over! ");
}

int main(int argc, char* argv[]) {
    char secretCode[CODE_LENGTH + 1] = "";
    int maxAttempts = MAX_ATTEMPTS;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                maxAttempts = atoi(argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                my_strncpy(secretCode, argv[i + 1], CODE_LENGTH);
                secretCode[CODE_LENGTH] = '\0';
                i++;
            }
        }
    }
    if (strcmp(secretCode, "") == 0) {
        generateSecretCode(secretCode);
    }
    playGame(secretCode, maxAttempts);
    return 0;
}

