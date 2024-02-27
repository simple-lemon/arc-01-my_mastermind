#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define CODELEN 4

typedef unsigned short flag;

static flag matched[CODELEN];

void mystrcpy(char *s1, char *s2) {
    while ((*s1++ = *s2++))
        ;
}

void generateCode(char *codeval) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < CODELEN; i++)
        codeval[i] = '0' + (rand() % 8);
}

int isValidInput(char c) {
    return (c >= '0' && c <= '8');
}

void readGuess(char *guess) {
    flag invalid;
    int i;
    char c;

    do {
        invalid = 0;
        i = 0;

        printf("Enter your guess: ");
        while (read(0, &c, 1) > 0 && c != '\n')
            if (isValidInput(c) && i < CODELEN)
                *(guess + i++) = c;
            else
                invalid = 1;

        *(guess + CODELEN) = '\0';

        if (c != '\n')
            printf("\n");

        if (!invalid && (i == CODELEN))
            break;

        if (i == 0) {
            for (i = 0; i < CODELEN; i++)
                *(guess + i) = -1;
            break;
        }

        printf("Wrong input! Please enter a valid guess using digits 0-8.\n");

    } while (1);
}

void evaluateGuess(char *guess, char *codeval, int *wellplaced, int *misplaced) {
    *wellplaced = 0;
    *misplaced = 0;

    for (int i = 0; i < CODELEN; i++) {
        if (guess[i] == codeval[i]) {
            matched[i] = 1;
            guess[i] = -1;
            (*wellplaced)++;
        }
    }

    for (int i = 0; i < CODELEN; i++) {
        if (guess[i] != -1) {
            for (int j = 0; j < CODELEN; j++) {
                if (!matched[j] && guess[i] == codeval[j]) {
                    matched[j] = 1;
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
}

void printResult(int wellplaced, char *codeval) {
    if (wellplaced == CODELEN)
        printf("Congratulations! You cracked the code %s!\n", codeval);
    else
        printf("Sorry, you lost. The correct code was %s.\n", codeval);
}

void restartGame(char *codeval) {
    printf("Starting a new game!\n");
    generateCode(codeval);
}

int main() {
    int tries = 10;
    int i;
    char codeval[CODELEN + 1] = {};
    char guess[CODELEN + 1];
    int wellplaced = 0;
    int misplaced = 0;

    generateCode(codeval);

    i = 0;
    printf("Will you find the secret code?\n");

    do {
        printf("Round %d\n", i + 1);
        for (int j = 0; j < CODELEN; j++)
            matched[j] = 0;

        readGuess(guess);

        evaluateGuess(guess, codeval, &wellplaced, &misplaced);

        if (wellplaced == CODELEN || ++i >= tries) {
            printResult(wellplaced, codeval);
            restartGame(codeval);
            i = 0;
            printf("Will you find the secret code?\n");
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellplaced, misplaced);
        }
    } while (1);

    return 0;
}
