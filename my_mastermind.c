


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *my_random();
int is_incorrect(char *input);
void parse_arguments(int argc, char **argv, int *attempts, char **code);
char *get_secret_code();
void evaluate_guess(char *input, char *code);
void play_game(int attempts, char *code);
void print_wrong_input();
void print_congratulations();
void print_well_missed(int well, int missed);
void print_round(int round);
void read_input(char *input);
void exit_game();
int generate_random_number();
void initialize_random();
void free_memory(char *code);
void set_initialized(int *initialized);
void allocate_memory(char **code);
void update_code(char *code, int num, int *used, int *count);
int count_digits(char *input);
void check_input_bounds(char *input);
void check_duplicates(char *input);
void count_well_missed(int *well, int *missed, int *code_used, int *input_used, char *input, char *code);
void print_prompt();
void get_input(char *input);
void process_input(char *input, char *code);
void handle_game_over(int well);
int main(int argc, char **argv);

char *my_random() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    char *code = (char *)malloc(sizeof(char) * 5);
    int used = 0, count = 0;
    while (count < 4) {
        int num = rand() % 9;
        if (!(used & (1 << num))) {
            code[count] = num + '0';
            used |= (1 << num);
            count++;
        }
    }
    code[4] = '\0';
    return code;
}

int is_incorrect(char *input) {
    if (strlen(input) != 4) {
        print_wrong_input();
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            print_wrong_input();
            return 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                print_wrong_input();
                return 1;
            }
        }
    }
    return 0;
}

void parse_arguments(int argc, char **argv, int *attempts, char **code) {
    *attempts = 10;
    *code = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            *attempts = atoi(argv[i + 1]);
            i++;
        } else if (strcmp(argv[i], "-c") == 0) {
            *code = argv[i + 1];
            i++;
        }
    }
}

char *get_secret_code() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    char *code = (char *)malloc(sizeof(char) * 5);
    int used = 0, count = 0;
    while (count < 4) {
        int num = rand() % 9;
        if (!(used & (1 << num))) {
            code[count] = num + '0';
            used |= (1 << num);
            count++;
        }
    }
    code[4] = '\0';
    return code;
}

void evaluate_guess(char *input, char *code) {
    int well = 0, missed = 0, code_used = 0, input_used = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == input[i]) well++;
        code_used |= (1 << (code[i] - '0'));
        input_used |= (1 << (input[i] - '0'));
    }
    int common = code_used & input_used;
    for (int i = 0; i < 9; i++) {
        if (common & (1 << i))
            missed++;
    }
    missed -= well;
    if (well == 4) {
        print_congratulations();
        exit_game();
    } else {
        print_well_missed(well, missed);
    }
}

void play_game(int attempts, char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15] = {0};
    for (int i = 0; i < attempts; i++) {
        print_round(i);
        do {
            print_prompt();
            read_input(input);
        } while (is_incorrect(input));
        evaluate_guess(input, code);
    }
}

void print_wrong_input() {
    printf("Wrong input!\n");
}

void print_congratulations() {
    printf("Congratz! You did it!\n");
}

void print_well_missed(int well, int missed) {
    printf("Well place pieces: %d\n", well);
    printf("Missed place pieces: %d\n", missed);
}

void print_round(int round) {
    printf("---\nRound %d\n", round);
}

void read_input(char *input) {
    char c = 0;
    int j = 0, flag = 1;
    while ((flag = read(0, &c, 1)) > 0) {
        if (c == '\n') {
            input[j] = '\0';
            break;
        }
        input[j] = c;
        j++;
    }
    if (flag == 0)
        exit_game();
}

void exit_game() {
    exit(0);
}

int generate_random_number() {
    return rand() % 9;
}

void initialize_random() {
    srand(time(NULL));
}

void free_memory(char *code) {
    free(code);
}

void set_initialized(int *initialized) {
    *initialized = 1;
}

void allocate_memory(char **code) {
    *code = (char *)malloc(sizeof(char) * 5);
}

void update_code(char *code, int num, int *used, int *count) {
    code[*count] = num + '0';
    *used |= (1 << num);
    (*count)++;
}

int count_digits(char *input) {
    return strlen(input);
}

void check_input_bounds(char *input) {
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            print_wrong_input();
            exit_game();
        }
    }
}

void check_duplicates(char *input) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]){
                print_wrong_input();
                exit_game();
            }
        }
    }
}
void count_well_missed(int *well, int *missed, int *code_used, int *input_used, char *input, char *code) {
    for (int i = 0; i < 4; i++) {
        if (code[i] == input[i]) (*well)++;
        *code_used |= (1 << (code[i] - '0'));
        *input_used |= (1 << (input[i] - '0'));
    }
    int common = *code_used & *input_used;
    for (int i = 0; i < 9; i++) {
        if (common & (1 << i))
            (*missed)++;
    }
    (*missed) -= (*well);
}

void print_prompt() {
    printf(">");
}

void get_input(char *input) {
    fgets(input, 15, stdin);
    strtok(input, "\n");
}

void process_input(char *input, char *code) {
    if (is_incorrect(input)) {
        print_wrong_input();
        return;
    }
    evaluate_guess(input, code);
}

void handle_game_over(int well) {
    if (well == 4) {
        print_congratulations();
    } else {
        printf("Game over! You couldn't guess the secret code.\n");
    }
    exit_game();
}

int main(int argc, char **argv) {
    int attempts;
    char *code;
    parse_arguments(argc, argv, &attempts, &code);
    if (!code) {
        code = my_random();
    }
    play_game(attempts, code);
    free_memory(code);
    return 0;
}
