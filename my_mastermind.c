#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int length(char* stroka){
    int index = 0;
    while ( stroka[index++]);
    return index - 1;
}


void copy(char* dest, char* source){
    for (int index = 0; index < length(source); index++){
        dest[index] = source[index];
    }
}


int string(char* stroka, char number){
    for(int index = 0; index < length(stroka); index++){
        if(stroka[index] == number)return 1;
    }
    return 0;
}

char* skan(){
    printf(">");
    fflush(stdout);
    char* input = calloc(5, sizeof(char));
    char temp;
    int index = 0;
    while(read(0,&temp, 1)){
        if( temp == '\n'){
            return input;
        }
        input[index] = temp;
        index++;
    }
    return NULL;
}


char* randomayzer(){

    char* random = calloc(5,sizeof(char));
    int index = 0;
    char temp;
    srand(time(0));
    while (index < 4){
        temp = rand() % 9 + 48;
        if ( string(random, temp) == 0){
            random[index] = temp;
            index++;
        }
        
    }
    return random;
}


int checking_alpha(char* input){
    for ( int index = 0; index < length(input); index++){
        if(!(input[index] >= 48 && input[index] <=56)){
            return 0;
        }
    }
    return 1;
}

int checkingdup(char* input){
    for (int index = 0; index < length(input); index++){
        for(int element = index + 1; element < length(input); element++){
            if (input[index] == input[element]) return 0;
        }
    }
    return 1;
}

int welplaced(char* sc_code, char* users_vvod){
    int count = 0;
    for (int index = 0; index < length(sc_code); index++){
        if(sc_code[index] == users_vvod[index]) count++;
    }
    return count;
}

int misplaced(char* sc_code, char* users_vvod){
    int count = 0;
    for(int index = 0; index < length(sc_code); index++){
        for( int element = 0; element < length(users_vvod); element++){
            if(sc_code[index] == users_vvod[element] && index != element) count++;
        }
    }
    return count;
}

int gen_checkning(char* input){
    if(length(input) != 4){
        return 0;
    }
    if(checking_alpha(input) == 0){
        return 0;
    }
    if(checkingdup(input) == 0){
        return 0;
    }

    return 1;
}


void main_func(int attemps, char* sc_code){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char* input;
    for (int index = 0; index < attemps; index++){
        printf("---\nRound %d\n",index);
        input = skan();
        if(vvod == NULL){
            return;
        }
        while(gen_checkning(input) == 0){
            free(input);
            printf("Wrong input!\n");
            input = skan();
        }
        int well = welplaced(sc_code,input);
        int miss = misplaced(sc_code,input);
        if ( well == 4){
            printf("Congratz! You did it!\n");
            return;
        }
        else{
            printf("Well placed pieces: %d\n", well);
            printf("Misplaced pieces: %d\n",miss);
        }
    }
}


int main(int argc, char** argv){
    int index = 0;
    char* secret_code = NULL;
    int attemps = 10;
    while (index < argc){
        if(strcmp(argv[index], "-c") == 0){
            index++;
            secret_code = malloc(sizeof(char) * 5);
            copy(secret_code, argv[index]);
            
        }
        else if(strcmp(argv[index], "-t") == 0){
            attemps = atoi(argv[index]);
            index++;
        }
    index++;
    }

    if( secret_code == NULL){
        secret_code = randomayzer();
    }

    main_func(attemps, secret_code);

    
    return 0;
}
