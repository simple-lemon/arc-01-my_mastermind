#ifndef MASTERMIND_H
#define MASTERMIND_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind_h.h"  
#define CD_LEN 4

char* initialize_game(int ac, char** av, int* MX_ATMT);
int play_game(char* scrt_cd, int MX_ATMT);
void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd);
char* randit(char* rndm_cd);
int validation(char* inpt);
int rd_input(char* user_guess);
int is_correct(int wlpcd);
void prnt_res(int wlpcd, int misd);

// strlen funksiyasi 
unsigned int my_strlen(const char* str){
    unsigned int len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}

// strcpy funksiyasi 
char* my_strcpy(char* dest, const char* src){
    char* start = dest;
    while((*dest++ = *src++) != '\0');
    return start;
}

// logikasi
int play_game(char* scrt_cd, int MX_ATMT){
    if(my_strlen(scrt_cd) != CD_LEN){
        srand(time(NULL));
        randit(scrt_cd);
    }
    char gues[CD_LEN + 1];
    int wel_plcd, misplcd, round = 0;
    printf("Will you find the secret code? \nPlease enter a valid numbers\n");

    while(round < MX_ATMT){
        printf("---\nRound %d\n>", round);
        fflush(stdout);
        
        if(rd_input(gues) != 0){
            printf("Wrong input!\n");
            continue;  
        }
        gues[CD_LEN] = '\0';

        if(!validation(gues)){
            continue;  
        }
        guess(gues, scrt_cd, &wel_plcd, &misplcd);

        if(is_correct(wel_plcd)){
            free(scrt_cd);
            return EXIT_SUCCESS;
        }
        prnt_res(wel_plcd, misplcd);
        round++;

        if(round == 10){
            printf("Sorry, you couldn't find the secret code.\n");
        }
    }
    free(scrt_cd);
    return EXIT_FAILURE;
}

// errorlari
int rd_input(char* guess){
    int chars_read = 0;
    char result;
    int frst_rn = 1;
    int count;

    while((count = read(STDIN_FILENO, &result, 1)) != -1){
        if(frst_rn && !count){
            exit(0);
        }
        if(frst_rn){
            frst_rn = 0;
        }

        if(result == '\n'){   
            guess[chars_read] = '\0';
            return 0;
        } 
        else if(chars_read >= CD_LEN){
            while(read(STDIN_FILENO, &result, 1) && result != '\n');
            return 1;
        } 
        else if(result < '0' || result > '9'){
            if(result == '\n'){
                exit(0);
            }
            while(read(STDIN_FILENO, &result, 1) && result != '\n');
            return 1;
        } 
        guess[chars_read++] = result;
    }
    return 1;
}

int is_correct(int wlplcd){
    if(wlplcd == 4){
        printf("Congratz! You did it!\n");
        return 1;
    }
    return 0;
}

void prnt_res(int wlplcd, int misd){
    printf("Well-placed pieces: %d\nMisplaced pieces: %d\n", wlplcd, misd);
}

// funksiyalari
void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd){
    *well_plcd = 0;
    *misplcd = 0;
    int gues_hist[10] ={0}; 
    int secret_hist[10] ={0}; 

    for(int i = 0; i < CD_LEN; i++){
        if(gues[i] == scrt_cd[i]){
           (*well_plcd)++;
        } 
        else{
            gues_hist[gues[i] - '0']++;
            secret_hist[scrt_cd[i] - '0']++;
        }
    }
    for(int i = 0; i < 10; i++){
        *misplcd += gues_hist[i] < secret_hist[i] ? gues_hist[i] : secret_hist[i];
    }
}

char* randit(char* rndm_cd){
    const char num[] = "012345678";
    for(int i = 0; i < CD_LEN; i++){
        rndm_cd[i] = num[rand() % 10];
    }
    rndm_cd[CD_LEN] = '\0';
    return rndm_cd;
}

int validation(char* inpt){
    if(my_strlen(inpt) != CD_LEN){
        printf("Wrong input!\n");
        return 0; 
    }
    int dig[10] ={0}; 

    for(int i = 0; i < CD_LEN; i++){
        if(inpt[i] < '0' || inpt[i] > '9' || inpt[i] == '9'){
            printf("Wrong input!\n");
            return 0; 
        }
        dig[inpt[i] - '0']++; 

        if(dig[inpt[i] - '0'] > 1){
            printf("Wrong input!\n");
            return 0; 
        }
    }
    return 1;
}

// -c va -t larni ishga tushirilishi
char* initialize_game(int ac, char** av, int* MX_ATMT){
    char* scrt_cd = calloc(sizeof(char), CD_LEN + 1);
    if(scrt_cd == NULL){
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < ac; i++){
        if(strcmp(av[i], "-c") == 0 && i + 1 < ac){
            my_strcpy(scrt_cd, av[i + 1]);
            scrt_cd[CD_LEN] = '\0';
        } 
        else if(strcmp(av[i], "-t") == 0 && i + 1 < ac){
            *MX_ATMT = atoi(av[i + 1]);
        }
    }
    return scrt_cd;
}
#endif