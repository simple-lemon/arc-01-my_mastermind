#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *generate_random_code();
int is_incorrect_input(char *input);
int count_well_placed(char *code, char *input);
int count_missed_placed(char *code, char *input);
void print_congratulations_message();
void print_attempt_message(int attempt);
char *read_user_input();
void initialize_input_buffer(char *input);
void process_user_input(char *input);
void print_well_and_missed(int well, int missed); 
void play_game(int attempts, char *code);
int get_attempts_from_arguments(int argc, char **argv);
char *get_code_from_arguments(int argc, char **argv);
void parse_command_line_arguments(int argc, char **argv, int *attempts, char **code);
void check_and_set_code_argument(char **code);
char *initialize_code(char *code);
void print_game_start_message();
void print_invalid_input_message();
void free_code_memory(char *code);
void free_input_memory(char *input);
char *my_strncpy(char *destination, char *source, size_t n);
int my_strcmp(const char *str1, char *str2);
size_t my_strlen(const char *str);

int main(int argc, char **argv) {
  int attempts;
  char *code;
  parse_command_line_arguments(argc, argv, &attempts, &code);
  if (code == NULL) {
    code = generate_random_code();
  }
  if (is_incorrect_input(code) == 1){
    return 1;
  } 
  print_game_start_message();
  play_game(attempts, code);
  free_code_memory(code);
  return 0;
}

char *generate_random_code() {
  srand(time(NULL));
  char *code = (char *)malloc(sizeof(char) * 5);
  for (int i = 0; i < 4; i++) {
    code[i] = rand() % 9 + '0';
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

int is_incorrect_input(char *input) {
  if (my_strlen(input) != 4) {
    return 1;
  }
  for (int i = 0; i < 4; i++) {
    if (input[i] < '0' || input[i] > '8'){
      return 1;
    } 
  }
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      if (input[i] == input[j]){
        return 1;
      }
    }
  }
  return 0; 
}

int count_well_placed(char *code, char *input) {
  int well = 0;
  for (int i = 0; i < 4; i++) {
    if (code[i] == input[i]){
      well++;
    }
  }
  return well;
}

int count_missed_placed(char *code, char *input) {
  int missed = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (input[i] == code[j] && i != j) { 
        missed++;
      }
    }
  }
  return missed;
}

void print_congratulations_message() {
  printf("Congratz! You did it!\n");
}

void print_attempt_message(int attempt) {
  printf("---\nRound %d\n", attempt);
}

char *read_user_input() {
  char *input = (char *)malloc(sizeof(char) * 15);
  initialize_input_buffer(input);
  char c = 0;
  int j = 0, flag = 1;
  do {
    write(1, ">", 1);
    for(j = 0;(flag = read(0, &c, 1)) > 0;) {
      if (c == '\n') {
        input[j] = '\0';
        break;
      }
      input[j] = c;
      j++;
    } 
    if (is_incorrect_input(input) == 1) print_invalid_input_message();
    if (flag == 0) return NULL;
  } while (is_incorrect_input(input));
  return input;
}

void initialize_input_buffer(char *input) {
  for (int i = 0; i < 15; i++) {
    input[i] = '\0';
  }
}

void process_user_input(char *input) {
  free_input_memory(input);
}

void print_well_and_missed(int well, int missed) {
  printf("Well place pieces: %d\n", well);
  printf("Missed place pieces: %d\n", missed);
}

void play_game(int attempts, char *code) {
  char *input;
  int well, missed;
  for (int i = 0; i < attempts; i++) {
    print_attempt_message(i);
    input = read_user_input();
    if (input == NULL) return;
    well = count_well_placed(code, input);
    missed = count_missed_placed(code, input);
    if (well == 4) {
      print_congratulations_message();
      process_user_input(input);
      return;
    } else {
      print_well_and_missed(well, missed);
      process_user_input(input);
    }
  }
}


int get_attempts_from_arguments(int argc, char **argv) {
  int attempts = 10;
  for (int i = 0; i < argc; i++) {
    if (my_strcmp(argv[i], "-t") == 0) {
      attempts = atoi(argv[i + 1]);
    }
  }
  return attempts;
}

char *get_code_from_arguments(int argc, char **argv) {
  char *code = NULL;
  for (int i = 0; i < argc; i++) {
    if (my_strcmp(argv[i], "-c") == 0) {
      code = (char *)malloc(sizeof(char) * 5);
      if (code == NULL) {
        return NULL;
      }
      my_strncpy(code, argv[i + 1], 5);
    }
  }
  return code;
}

void parse_command_line_arguments(int argc, char **argv, int *attempts, char **code) {
  *attempts = get_attempts_from_arguments(argc, argv);
  *code = get_code_from_arguments(argc, argv);
  check_and_set_code_argument(code);
}

void check_and_set_code_argument(char **code) {
  if (*code == NULL) {
    *code = initialize_code(*code);
  }
}

char *initialize_code(char *code) {
  return code;
}

void print_game_start_message() {
  printf("Will you find the secret code?\nPlease enter a valid guess:\n");
}

void print_invalid_input_message() {
  printf("Wrong input!\n");
}

void free_code_memory(char *code) {
  if (code != NULL){
    free(code);
  }
}

void free_input_memory(char *input) {
  if (input != NULL){
    free(input);
  }
}

char *my_strncpy(char *destination, char *source, size_t n) {
  if (destination == NULL || source == NULL) {
    return NULL;
  }
  char *ptr = destination;
  size_t i = 0;
  while (i < n && *source != '\0') {
    *destination = *source;
    destination++;
    source++;
    i++;
  }
  while (i < n) {
    *destination = '\0';
    destination++;
    i++;
  }
  return ptr;
}

int my_strcmp(const char *str1, char *str2) {
  while (*str1 != '\0' && *str2 != '\0') {
    if (*str1 != *str2){
      return (*str1 - *str2);
    }
    str1++;
    str2++;
  }
  return (*str1 - *str2);
}

size_t my_strlen(const char *str) {
  size_t length = 0;
  while (*str != '\0') {
    length++;
    str++;
  }
  return length;
}
