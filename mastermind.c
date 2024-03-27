#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind_h.h"
#define CD_LEN 4

int MX_ATMT = 10; 

int main(int ac, char** av){
    char* scrt_cd = initialize_game(ac, av, &MX_ATMT);
    int result = play_game(scrt_cd, MX_ATMT);
    
    return result;
}