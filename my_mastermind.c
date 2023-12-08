#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#define CODE_LENGTH 4
char *my_scanf()
{
  int size = 10;
  char *user_input = calloc(sizeof(char), size);
  int index = 0;
  char temp;
  while (read(0, &temp, 1))
  {
    if (temp == '\n')
    {
      user_input[index] = '\0';
      return user_input;
    }
    user_input[index++] = temp;
    if (index >= size - 1)
    {
      size *= 2; // Double the size of the buffer
      user_input = realloc(user_input, size);
      if (user_input == NULL)
      {
        // Handle memory reallocation failure
        exit(EXIT_FAILURE);
      }
    }
  }
  free(user_input);
  return NULL;
}

bool isNumberPresent(int num, char *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == num)
    {
      return true;
    }
  }
  return false;
}

char *my_strchr(char *param_1, char param_2)
{
  int i = 0;
  while (param_1[i] != '\0')
  {
    if (param_1[i] == param_2)
    {
      return &param_1[i];
    }
    i++;
  }
  if (param_1[i] != param_2)
  {
    return NULL;
  }
  return &param_1[i];
}

int my_atoi(char *param_1)
{
  int result = 0;
  for (int i = 0; param_1[i] != '\0'; i++)
  {
    result = result * 10 + (param_1[i] - '0');
  }
  return result;
}

int isDigit(char *str, int size)
{
  for (int i = 0; i < size + 1; i++)
  {
    if ((str[i] < '0' || str[i] > '8') || str[i] == '9')
    {
      return 1;
    }
  }
  return 0;
}

int my_strcmp(char *p1, char *p2)
{
  for (int i = 0; p1[i] || p2[i]; i++)
  {
    if (p1[i] != p2[i])
    {
      return p1[i] - p2[i];
    }
  }
  return 0;
}
int my_strlen(char *str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  return i;
}

void generateSecretCode(char *secret)
{
  srand((unsigned)time(NULL));
  for (int i = 0; i < CODE_LENGTH; ++i)
  {
    char digit;
    do
    {
      digit = rand() % 9 + '0';
    } while (my_strchr(secret, digit) != NULL);
    secret[i] = digit;
  }
  secret[CODE_LENGTH] = '\0';
}

bool isValidGuess(char *guess)
{
  for (int i = 0; i < CODE_LENGTH; ++i)
  {
    if (!isdigit(guess[i]) || isNumberPresent(guess[i], guess, i))
    {
      return false;
    }
  }
  return my_strlen(guess) == CODE_LENGTH;
}

char *getUserGuess()
{
  printf(">");
  fflush(stdout);
  char *guess = my_scanf();
  if (guess == NULL)
    return NULL;
  do
  {
    if (!isValidGuess(guess))
    {
      printf("Wrong input!\n");
      printf(">");
      fflush(stdout);
      free(guess);
      guess = my_scanf();
    }
  } while (!isValidGuess(guess));
  return guess;
}

void evaluateGuess(char *secret, char *guess)
{
  int wellPlaced = 0;
  int misplaced = 0;
  for (int i = 0; i < CODE_LENGTH; ++i)
  {
    if (guess[i] == secret[i])
    {
      wellPlaced++;
    }
    else if (my_strchr(secret, guess[i]) != NULL)
    {
      misplaced++;
    }
  }
  printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
}

void main_f(char *secret, int move)
{
  if (!isValidGuess(secret))
    exit(1);
  printf("Will you find the secret code?\nPlease enter a valid guess\n");
  for (int round = 0; round < move; round++)
  {
    printf("---\n");
    printf("Round %d\n", round);
    char *guess = getUserGuess();
    if (guess == NULL)
      return;

    if (my_strcmp(secret, guess) == 0)
    {
      printf("Congratz! You did it!\n");
      free(guess);
      exit(0);
    }
    else
    {
      evaluateGuess(secret, guess);
    }
    free(guess);
  }
}

void check_av(int argc, char **argv)
{
  char secret_c[CODE_LENGTH + 1];
  generateSecretCode(secret_c);
  if (argc < 2)
  {
    main_f(secret_c, 10);
  }
  else if (argc == 3 && (my_strcmp(argv[1], "-c") == 0))
  {
    main_f(argv[2], 10);
  }
  else if (argc == 3 && (my_strcmp(argv[1], "-t") == 0))
  {
    main_f(secret_c, my_atoi(argv[2]));
  }
}
int main(int argc, char **argv)
{
  check_av(argc, argv);
  return 0;
}
