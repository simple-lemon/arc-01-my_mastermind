#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int my_strlen(char* input) 
{
    int length = 0;

    while(input[length] != '\0')
    {
        length++;
    }
    return length;
}



int check_input(char *input) 
{
    for (int i = 0; i < 4; i++) 
    {
        if (my_strlen(input) != 4 || input[i] < '0' || input[i] > '8') 
        {
            printf("Wrong input!\n");
            return 1;
        }
    }

    for (int i = 0; i < 4; i++) 
    {
        for (int j = i + 1; j < 4; j++) 
        {
            if (input[i] == input[j]) 
            {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    return 0;    
}



char *generateSecretCode() 
{
    srand(time(NULL));
    char *secret_code = (char *)malloc(5 * sizeof(char));

    for (int i = 0; i < 4; i++) 
    {
        secret_code[i] = rand() % 9 + '0';

        for (int j = 0; j < i; j++) 
        {
            if (secret_code[i] == secret_code[j]) 
            {
                i--;
                break;
            }
        }
    }
         secret_code[4] = '\0';
         return secret_code;
}


int read_input(char *input) 
{
    char text;
    int j = 0;
    int cache = 1;

    do {
        write(1, ">", 1);
        j = 0;

        while ((cache = read(0, &text, 1)) > 0) 
        {
            if (text == '\n') 
            {
                input[j] = '\0';
                break;
            }
                input[j] = text;
                j++;
        }
             if (cache == 0){
             return 0;
        }
    }

    
     while (check_input(input));
     return 1;
}



int check_num(char *input, char *secret_code) 
{
    int well = 0;
    int miss = 0;

    for (int i = 0; i < 4; i++) 
    {
        if (secret_code[i] == input[i]) 
        {
            well++;
        }
    }

    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            if (input[i] == secret_code[j] && i != j) 
            {
                miss++;
            }
        }
    }

    if (strcmp(input, secret_code) == 0) 
    {
        printf("Congratz! You did it!\n");
        return 1;
    } 
    else 
    {
        printf("Well placed pieces: %d\nMissed placed pieces: %d\n", well, miss);
        return 0;
    }
}



void play_game(int max_attempts, char *secret_code)
{
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    char input[30] = {0};
    int game_won = 0;

    for (int i = 0; i < max_attempts && !game_won; i++) 
    {
        printf("---\nRound %d\n", i);
        int is_valid_input = read_input(input);

        if (!is_valid_input) return;
        game_won = check_num(input, secret_code);
    }
}


int main(int argc, char **argv) 
{
    int max_attempts = 10;
    char *secret_code = NULL;

    for (int i = 0; i < argc; i++) 
    {
        if (strcmp(argv[i], "-t") == 0) 
        {
            max_attempts = atoi(argv[i + 1]);
        }

        if (strcmp(argv[i], "-c") == 0) 
        {
            secret_code = argv[i + 1];
        }
    }

    if (secret_code == NULL) 
    {
        secret_code = generateSecretCode();
    }

    play_game(max_attempts, secret_code);

    if (secret_code != NULL) 
    {
        free(secret_code);
    }
        return 0;
}
