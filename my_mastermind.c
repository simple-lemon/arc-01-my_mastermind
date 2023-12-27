#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "my_mastermind.h"
int valid_code(char *str){
    int length = strlen(str);
    int count, i, j;
    if(length!=4){
        return 0;
    }
    for(i=0; i<length; i++){
        if(str[i]<'0' || str[i]>'8'){
            return 0;
        }
    }
    for(i=0; i<length; i++){
        count = 0;
        for(j=0; j<length; j++){
            if(str[i]==str[j]){
                count++;
                if(count>1){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int valid_attempts(char *string){
    for(int i=0; i<strlen(string); i++){
        if(string[i]<'0' || string[i]>'8'){
            return 0;
        }
    }
    return 1;
}
int wellMiss(char *str1, char *str2){
    if(str2[0]=='\0'){
        return 1;
    }
    if(!valid_code(str2)){
        printf("Wrong input");
        return 0;
    }
    int i, j, counter1, counter2;        
        counter1 = 0;
        counter2 = 0;
    for(i=0; i<strlen(str1); i++){
        if(str1[i]==str2[i]){
            counter1++;
        }
    }    
    for(i=0; i<strlen(str2); i++){
        for(j=0; j<strlen(str2); j++){
            if(str1[i]!=str2[i] && str1[i]==str2[j] ){
                counter2++;
            }
        }
    }
   if(counter1 == 4){
        printf("Congratz you did it\n");
        return 1;
    }else{
        printf("Well placed place %d\n", counter1);
        printf("Miss placed place %d\n", counter2);
    }
    return 0;
}
int checkRand(char *str){
   int count;
      for(int i=0; i<4; i++){
        count = 0;
        for(int j=0; j<4; j++){
            if(str[i]==str[j]){
                count++;
                if(count>1){
                  return 1;
                }
            }
        }
    }
    return 0;
}
char *randNum(){
   srand(time(0));
   char *randStr = calloc(5, sizeof(char));
   while(checkRand(randStr)){
      for(int i=0; i<4; i++){
         randStr[i] = rand()%9 + '0';
      }  
   }
    return randStr;
}
int createAttempt(){
    int attempt = 10;
    return attempt;
}
int main(int argc, char**argv){
    char *secret_code = calloc(5, sizeof(char));
    int attempts;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-c"))
        {
            i++;            
            if (!valid_code(argv[i]))
            {
                printf("Invalid code!\n");
                return 1;
            }
            strcpy(secret_code, argv[i]);
        }
        else if (!strcmp(argv[i], "-t"))
        {
            i++;
            if (!valid_attempts(argv[i]))
            {
                printf("Invalid attempts!\n");
                return 1;
            }

            attempts = atoi(argv[i]);
        }
    }
    if(secret_code[0] == '\0'){
        secret_code = randNum();
    }            
    if(!attempts){
        attempts = createAttempt();
    }

    char *useCode = calloc(5, sizeof(char));
    useCode[4]='\0';
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int i=0; i<attempts; i++){
        int j = 0;
        int flag = 1;
        char c;
        printf("---\nRound %d\n>",i);
        fflush(stdout);
        while(flag = read(0, &c, 1)){
           if(c=='\n') break;
          useCode[j++] = c;
        }
        useCode[j]='\0';
        if(flag==0){
            free(secret_code);
            free(useCode);
            return 0;
        }
        if(wellMiss(secret_code, useCode)){
            free(secret_code);
            free(useCode);
            return 1;
        }
        
                   
    }
    printf("%s", secret_code);
    free(secret_code);
    free(useCode);
    return 0;
}

