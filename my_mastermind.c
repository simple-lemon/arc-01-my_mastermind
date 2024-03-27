#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4

int my_strlen(char *guess){
    int counter = 0;
    for (int i = 0; guess[i]; i++){
        counter++;
    }

    return counter;
}

int my_strcmp(const char *str1, const char *str2){
    while (*str1 && *str2 && *str1 == *str2){
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void my_strncpy(char *dest, const char *src, size_t n){
    for (size_t i = 0; i < n && src[i] != '\0'; i++){
        dest[i] = src[i];
    }
    dest[n] = '\0';
}

void GenerateSecretCode(char *code){
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++){
        int digit;
        do{
            digit = rand() % 9 + 1;
            int found = 0;
            for (int j = 0; j < i; j++){
                if (code[j] == digit + '0'){
                    found = 1;
                    break;
                }
            }
            if (!found){
                code[i] = digit + '0';
                break;
            }
        } while (1);
    }
    code[CODE_LENGTH] = '\0';
}

int CheckValidGuess(char *guess){
    if (my_strlen(guess) != CODE_LENGTH){
        return 0;
    }
    for (int i = 0; i < CODE_LENGTH; i++){
        if (guess[i] < '0' || guess[i] > '8'){
            return 0;
        }
        for (int j = i + 1; j < CODE_LENGTH; j++){
            if (guess[i] == guess[j]){
                return 0;
            }
        }
    }
    return 1;
}

void ReadGuess(char *guess){
    char c;
    int i = 0;
    write(1, ">", 1);
    while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n'){
        guess[i++] = c;
    }
    guess[i] = '\0';

    if (i == 0){
        write(1, "\n", 1);
        exit(0);
    }
    while (c != '\n' && read(STDIN_FILENO, &c, 1) > 0);
}

int CounterPlaces(char *secretCode, char *guessCode){
    int well_placed = 0, misplaced = 0, i = 0, j = 0;
    do{
        if (secretCode[i] == guessCode[i]){
            well_placed++;
        }else{
            do{
                misplaced++;
                j++;
                break;
            }while(j < CODE_LENGTH);
        }
        i++;
    } while (i < CODE_LENGTH);

    if (well_placed == CODE_LENGTH){
        return 1;
    }

    printf("Well placed pieces: %d\n", well_placed);
    printf("Misplaced pieces: %d\n", misplaced);
    return 0;
}

void UserAttempts(char *secretCode, char *guessCode, int maxRounds){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int round = 0; round < maxRounds; round++){
        printf("---\nRound: %d\n", round);
        ReadGuess(guessCode);
        if (!CheckValidGuess(guessCode)){
            round--;
            printf("Wrong input!\n");
            continue;
        }
        else if (CounterPlaces(secretCode, guessCode) == 1){
            printf("Congratz! You did it!\n");
            break;
        }
    }
}

int main(int argc, char *argv[]){
    char secretCode[CODE_LENGTH + 1] = {0};
    char guessCode[CODE_LENGTH + 1];
    int maxRounds = 10;

    for (int i = 1; i < argc; i++){
        if (*(argv[i]) == '-' && argv[i][1] == 'c' && i + 1 < argc){
            int len = my_strlen(argv[i + 1]);
            if (len != CODE_LENGTH){
                printf("Wrong input!\n");
                return 1;
            }

            for (int j = 0; j < len; j++){
                if (argv[i + 1][j] < '0' || argv[i + 1][j] > '8'){
                    return 1;
                }
                for (int k = j + 1; k < len; k++){
                    if (argv[i + 1][j] == argv[i + 1][k])
                    {
                        return 1;
                    }
                }
            }
            my_strncpy(secretCode, argv[i + 1], CODE_LENGTH);
        }
        else if (*(argv[i]) == '-' && argv[i][1] == 't' && i + 1 < argc)
        {
            maxRounds = atoi(argv[i + 1]);
        }
    }

    if (!secretCode[0])
    {
        GenerateSecretCode(secretCode);
    }

    UserAttempts(secretCode, guessCode, maxRounds);
    return 0;
}