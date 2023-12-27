#ifndef MASTERMIND
#define MASTERMIND
int valid_code(char *str);
int valid_attempts(char *string);
int wellMiss(char *str1, char *str2);
int checkRand(char *str);
char *randNum();
int createAttempt();
#endif