#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define DEFAULT_ATTEMPTS 10

void arg_process(int argc, char **argv, int *attempts, char **secret_code);
char *scrtcode_generator();
void get_input(char *input);
void gameplay(int attempts, char *secret_code);
size_t my_strlen(const char *str);
int valid_input_test(char *input);

int main (int argc, char **argv) {
    int attempts = DEFAULT_ATTEMPTS;
    char *secret_code = NULL;

    arg_process(argc, argv, &attempts, &secret_code);
    gameplay(attempts, secret_code);
    return 0;
}

void arg_process(int argc, char **argv, int *attempts, char **secret_code) {
    for (int i = 0; i < argc; i++){
        if (strcmp (argv[i], "-t") == 0) {
            *attempts = atoi (argv[i + 1]);
        }
        if (strcmp (argv[i], "-c") == 0) {
            *secret_code = argv[i + 1];
        }
    }
    if (*secret_code == NULL) {
        *secret_code = scrtcode_generator();
    }
}

char *scrtcode_generator() {
    srand (time (NULL));
    char *secret_code = (char *)calloc(sizeof(char), CODE_LENGTH + 1);
    for (int i = 0; i < CODE_LENGTH; i++) {
        secret_code[i] = rand () % 9 + '0';
        for (int j = 0; j < i; j++) {    
            if(secret_code[i] == secret_code[j]) {
                i--;
            }
        }
    }
    secret_code[CODE_LENGTH] = '\0';
    return secret_code;
}

void get_input(char *input) {
    char c = '\0';
    int abort, j;
    do {
        write (1,">", 1);
        j = 0;
        while ((abort = read (0, &c, 1)) > 0) {
            if (c == '\n') {
                input[j] = '\0';
                break;
            }
            input[j] = c;
            j++;
        }
    } while (valid_input_test (input));

    if (abort == 0) {
        return 0;
    }
}

void gameplay(int attempts, char *secret_code) {
    printf ("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int i = 0; i < attempts; i++) {
        printf ("---\nRound %d\n", i);
        char input[CODE_LENGTH + 1] = {0};
        get_input(input);

        int wellplaced = 0, misplaced = 0;
        for (int i = 0; i < CODE_LENGTH; i++) {
            if(secret_code[i] == input[i]) wellplaced++;
        }
        for(int i = 0; i < CODE_LENGTH; i++) {
            for(int j = 0; j < CODE_LENGTH; j++){
                if(input[i] == secret_code[j] && i != j) misplaced++;
            }
        }
        if (wellplaced == CODE_LENGTH) {
            printf ("Congratz! You did it!\n");
            return;
        } else {
            printf("Wellplaced pieces: %d\n", wellplaced);
            printf("Misplaced pieces: %d\n", misplaced);
        }
    }
}

size_t my_strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return s - str;
}

int valid_input_test(char *input) {
    if (my_strlen (input) != CODE_LENGTH) {
        printf("Wrong input!\n");
        return 1;
    } 
    
    for (int i = 0; i < CODE_LENGTH; i++){
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 2;
        }
    }
    
    for (int i = 0; i < CODE_LENGTH; i++){
        for (int j = i + 1; j < CODE_LENGTH; j++) {
            if (input[i] == input[j]) {
                printf ("Wrong input!\n");
                return 3;
            }
        }
    }
    return 0;
}