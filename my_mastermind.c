#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define ERROR false
#define CODE_LENGTH 4

char *allocate_memory(int size) {
    char *entry = calloc(sizeof(char), size);
    if (entry == NULL){
        return ERROR;
    }
    return entry;
}

char *resize_entry(char *entry, int *r_size) {
    *r_size *= 2;
    char *new_entry = realloc(entry, *r_size);
    if (new_entry == NULL) {
        return ERROR;
    }
    return new_entry;
}

char *scan_func() {
    int r_size = 8;
    char temp;
    int i = 0;
    char *entry = allocate_memory(r_size);
    ssize_t ret;
    while ((ret = read(0, &temp, 1)) > 0) {
        if (temp == '\n') {
            entry[i] = '\0';
            return entry;
        }
        entry[i++] = temp;
        if (i >= r_size) entry = resize_entry(entry, &r_size);
    }
    free(entry);
    return NULL;
}

int b_search(char *array, int left, int right, int number) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (array[mid] == number){
            return mid;
        }
        if (array[mid] > number){
            return b_search(array, left, mid - 1, number);
        }
        return b_search(array, mid + 1, right, number);
    }
    return -1;
}

int isNumber(int number, char *array, int r_size) {
    int result = b_search(array, 0, r_size - 1, number);
    if (result != -1) {
        return true;
    }    
    else {
        return false;
    }
}

char *str_chr(char *a, char b) {
    int w = 0;
    while (a[w]) {
        if(a[w] == b)
        return &a[w];
        w++;
    }
    return 0;
}

int my_str_len(char *str) {
    int w = 0;
    while (str[w]) {
        w++;
    }
    return w;
}

char *strn_cpy(char *str1, const char *str2, int n) {
    char *dest = str1;
    int i;
    for (i = 0; i < n && str2[i] != '\0'; i++) {
        dest[i] = str2[i];
    }
    dest[i] = '\0';
    return dest;
}

void generate_code(char* secret,int r_size) {
    srand((unsigned)time(NULL));
    char temp;
    int i = 0;
    while (i < CODE_LENGTH){
        temp = rand() % r_size + '0';
        if (str_chr(secret, temp) == 0){
            secret[i] = temp;
            i++;
        }
    }
    secret[CODE_LENGTH] = '\0';
}

int Prediction(char *guess) {
    int i = 0;
    for (;i < CODE_LENGTH; ++i) {
        if ((guess[i] < '0' || guess[i] > '8') || isNumber(guess[i], guess, i)) {
        return 0;
        }
    }
    return my_str_len(guess) == CODE_LENGTH;
}

char *assessGuess() {
    char *guess = scan_func();
    while (guess != NULL && !Prediction(guess)) {
        printf("Wrong input!\n> ");
        guess = scan_func();
    }
    return guess;
}

void Guess(char *secret_code, char *guess) {
    int wellPlaced = 0;
    int missplaced = 0;
    for (int i = 0; i < CODE_LENGTH; ++i) {
        if (guess[i] == secret_code[i]) {
            wellPlaced++;
        }
        else if (str_chr(secret_code, guess[i]) != NULL) {
            missplaced++;
        }
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, missplaced);
}

int main_f(char *secret_code, int move) {
    if (!Prediction(secret_code)) return ERROR;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int round = 1; round <= move; round++) {
        printf("---\nRound %d\n> ", round);
        char *guess = assessGuess();
        if (guess == NULL){
            return ERROR;
        }
        if (strcmp(secret_code, guess) == 0) {
            printf("Congratz! You did it!\n");
            return 0;
        } else {
            Guess(secret_code, guess);
        }
    }
    return 0;
}

void analyzer(int argc, char *argv[], char *secret_code, int *rounds, bool *secret_c) {
    if (argc > 1) {
      for (int i = 1; i < argc; ++i) {
        if ((argc >= 3 && strcmp(argv[i],"-c") == 0) && i+1 < argc) {
            strn_cpy(secret_code, argv[i+1], CODE_LENGTH);
            *secret_c = true;
        }
        else if ((argc >= 3 && strcmp(argv[i],"-t") == 0) && i+1 < argc) {
            *rounds = atoi(argv[i+1]);
        }
      }
    }
}

int main(int argc, char*argv[]) {
    char secret_code[CODE_LENGTH + 1] = {0};
    bool secret_c = false;
    int rounds = 10;
    if (argc % 2 == 0) {
        return ERROR;
    }
    else {
        analyzer(argc, argv, secret_code, &rounds, &secret_c);
    }
    if(secret_c == false) {
        generate_code(secret_code, CODE_LENGTH);
    }
    if(rounds != 0) {
        main_f(secret_code, rounds);
    }
    return 0;
}