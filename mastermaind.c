#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CODELEN 5

typedef unsigned short flag;

static flag matched[CODELEN] = {0};

void mystrcpy(char *, char *);
void readinput(char *);
int count_wellplaced(char *, char *);
int count_misplaced(char *, char *);

void mystrcpy(char *s1, char *s2) {
    while ((*s1++ = *s2++))
        ;
}

void readinput(char *buf) {
    flag invalid;
    int i;
    char c;

    do {
        invalid = 0;
        i = 0;

        while (scanf("%c", &c) > 0 && c != '\n') {
            if (c >= '0' && c <= '8' && i < CODELEN)
                *(buf + i++) = c;
            else
                invalid = 1;
        }

        *(buf + CODELEN) = '\0';

        if (c != '\n')
            printf("\n");

        if (!invalid && (i == CODELEN))
            break;

        if (i == 0) {
            for (i = 0; i < CODELEN; i++)
                *(buf + i) = -1;
            break;
        }

        printf("Wrong input!\n");

    } while (1);
}

int count_wellplaced(char *guess, char *codeval) {
    int wellplaced, i;
    for (wellplaced = 0, i = 0; i < CODELEN; i++, guess++, codeval++) {
        if (*guess == *codeval) {
            matched[i] = 1;
            *guess = -1;
            wellplaced++;
        }
    }
    return wellplaced;
}

int count_misplaced(char *guess, char *codeval) {
    int misplaced, i;
    for (misplaced = 0; *guess != '\0'; guess++) {
        for (i = 0; i < CODELEN; i++) {
            if (!matched[i] && *(codeval + i) == *guess) {
                matched[i] = 1;
                misplaced++;
                break;
            }
        }
    }
    return misplaced;
}

void generate_code(char *codeval) {
    int i;
    for (i = 0; i < CODELEN; i++)
        codeval[i] = '0' + (rand() % 8);
    codeval[CODELEN] = '\0';
}

void print_code(char *codeval) {
    printf("Secret Code: %s\n", codeval);
}

int main() {
    srand(time(NULL));
    char codeval[CODELEN + 1];
    char guess[CODELEN + 1];
    int wellplaced, misplaced;

    generate_code(codeval);
    print_code(codeval);

    printf("Will you find the secret code?\n");

    while (1) {
        printf("Enter your guess: ");
        readinput(guess);

        wellplaced = count_wellplaced(guess, codeval);
        misplaced = count_misplaced(guess, codeval);

        if (wellplaced == CODELEN) {
            printf("Congratulations! You found the secret code.\n");
            break;
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellplaced, misplaced);
        }
    }

    return 0;
}