#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define the_length_of_param 4
void function_c(char* param_1, char* param_2, int* val, int* res)
{
    int i = 0; *val=0,*res=0;   
    int param_1_param_1[10] = {0};
    int c1[10] = {0};
    for (int i = 0; i < the_length_of_param; i++){
        if (param_1[i] == param_2[i]){
            (*val)++;
        } else {
            param_1_param_1[param_1[i] - '0']++;
            c1[param_2[i] - '0']++;
        }
    }
    while(i<10){
        if (c1[i] < param_1_param_1[i]){
            *res += c1[i];
        } else {
            *res += param_1_param_1[i];
        }
        i++;
    }
}

char* function_in_c(char* ptr)
{
    const char numbers[] = "0123456789";
    int a1 = 0;
    while(a1<the_length_of_param){
        ptr[a1] = numbers[rand() % 10];
        a1++;
    }
    ptr[the_length_of_param] = '\0';
    return ptr;
}

int function_input(char* input_code)
{
    int i = 0;
    if (strlen(input_code) != the_length_of_param){
        return 0;
    }
    
    while(i<the_length_of_param){
        if (input_code[i] < '0' || input_code[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}



int main(int argc, char** argv)
{
    char* the_param_2 = calloc(sizeof(char), the_length_of_param + 1);
    int attmep = 10;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(the_param_2, argv[i + 1], the_length_of_param);
            the_param_2[the_length_of_param] = '\0';
        }else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            attmep = atoi(argv[i + 1]);
        }
    }
    if (strlen(the_param_2) == 0){
        srand(time(NULL));
        function_in_c(the_param_2);
    }
    char param_1[the_length_of_param + 1];
    int val, res;
    int rounds = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (rounds < attmep){
        printf("---\nRound %d\n>", rounds);
        if (read(0, param_1, the_length_of_param + 1) == -1){
            printf("Error reading input.\n");
            return 1;
        }
        param_1[the_length_of_param] = '\0';
        if (!function_input(param_1)){
            printf("res input!\n");
            continue;
        }
        function_c(param_1, the_param_2, &val, &res);
        if (val == the_length_of_param){
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", val, res);
        rounds++;
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}