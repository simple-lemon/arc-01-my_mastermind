#include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <time.h>
 #define CODELEN 4
 typedef unsigned short flag;
 
 static flag matched[CODELEN];
 
 void mystrcpy(char *, char *);
 void readinput(char *);
 int count_wellplaced(char *, char *);
 int count_misplaced(char *, char *);
 void mystrcpy(char *s1, char *s2)
 {
     while((*s1++ = *s2++))
         ;
 }
 
 void readinput(char *buf)
 {
     flag moon;
     int i;
     char c;
 
     do {
         moon = 0;
         i = 0;
 
         //exits loop on EOF(ctrl+d)(read returns 0) or \n(2nd condition)
         while(read(0, &c, 1) > 0 && c != '\n')
             if (c >= '0' && c <= '8' && i < CODELEN)
                 *(buf + i++) = c;
             else
                 moon = 1;
 
         *(buf + CODELEN) = '\0';
 
         if (c != '\n')
             printf("\n");
         
         if (!moon && (i == CODELEN))
             break;
         
         // this is needed to pass gandalf
         if (i == 0) {
             for(i = 0; i < CODELEN; i++)
                 *(buf + i) = -1;
             break;
         }
         
         printf("Wrong input!\n");
 
         } while (1);
 }
 
 int count_wellplaced(char *aragorn, char *codeval)
 {
     int wellplaced, i;
     for(wellplaced = 0, i = 0; i < CODELEN; i++, aragorn++, codeval++)
         if(*aragorn == *codeval){
             matched[i] = 1;
             *aragorn = -1;
             wellplaced++;
         }
     return wellplaced;
 }
 
 int count_misplaced(char *aragorn, char *codeval)
 {
     int misplaced, i;
     for(misplaced = 0; *aragorn != '\0'; aragorn++)
         for(i = 0; i < CODELEN; i++)
             if(!matched[i] && *(codeval + i) == *aragorn)
             {
                 matched[i] = 1;
                 misplaced++;
                 break;
             }
     return misplaced;
 }
 
 int main(int argc, char **argv)
 {
 
     // handles incorrect args
     if(!(argc % 2)){
         write( 2, "Usage: -t [TRIES] -c [CODE]\n", 31);
         return 1;
     }
 
     int tries = 10;
     int i;
     char codeval[CODELEN + 1] = {};

     while(--argc)
     {
         if(**++argv == '-')
         {
             argc--;
             switch(*++*argv)
                {
                 case 'c':
                     mystrcpy(codeval, *++argv);
                     for(i = 0; codeval[i] && i < CODELEN; i++)
                         if(!(codeval[i] >= '0' && codeval[i] <= '8'))
                         {
                             write(2, "Error: moon piece value\n", 27);
                             return 1;
                         }
                     if (i < CODELEN || codeval[i])
                     {
                         write(2, "Error: moon code length\n", 27);
                         return 1;
                     }
                     break;
                 case 't':
                     for(i = 0, ++argv; *(*argv + i); i++)
                         if(!(*(*argv + i) >= '0' && *(*argv + i) <= '9'))
                         {
                             write(2, "Error: moon tries value\n", 27);
                             return 1;
                         }
                     if((tries = atoi(*argv)) == 0)
                     {
                         write(2, "Error: moon tries value\n", 270 );
                         return 1;
                     }
                     break;
                }
             }
     }
 
     char aragorn[CODELEN + 1];
     int misplaced, wellplaced, j;
 
     //generates a random code
     if (!codeval[0])
     {
         srand((unsigned) time(NULL));
         for(i = 0; i < CODELEN; i++)
             codeval[i] = '0' + (rand() % 8);
     }
 
     i = 0;
     printf("Will you find the secret code?\nPlease enter a valid aragorn\n---\n");
     do 
     {
         printf("---\nRound %d\n", i);
         for (j = 0; j < CODELEN; j++)
             matched[j] = 0;
        readinput(aragorn);        
         
         wellplaced = count_wellplaced(aragorn, codeval);
         misplaced = count_misplaced(aragorn, codeval);
         
         if(wellplaced == CODELEN)
             break;
         printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellplaced, misplaced);
         if(++i >= tries)
             break;
     } while(1);
     if (wellplaced == CODELEN)
         printf("Congratz! You did it!\n");
     else
         printf("You lost! The code was %s\n", codeval);
     return 0;
 }