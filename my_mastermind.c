#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int my_strchr(char* str, char c) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}

char* my_rand(char* secret_code) {
    int i = 0;
    srand(time(0));
    char valid_numbers;
    
    while (i < 4) {
        valid_numbers = (rand() % 10) + '0'; 
        if (my_strchr(secret_code, valid_numbers) == 0) {
            secret_code[i++] = valid_numbers;
        }
    }
    return secret_code;
}

int my_atoi(char* str) {
    int i = 0;
    int num = 0;
    int flag = 0;

    if (str[i] == '-') {
        flag = 1;
        i = 1;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        num *= 10;
        num = num + (str[i++] - '0');
    }

    if (flag == 1) {
        num *= -1;
    }

    return num;
}

int my_strlen(char* str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

int my_strcmp(char* p1, char* p2) {
    int len1 = my_strlen(p1);
    int len2 = my_strlen(p2);

    if (len1 != len2) {
        return len1 - len2;
    }

    for (int i = 0; i < len1; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }

    return 0;
}

char* my_strcpy(char* c1, char* c2) {
    int i = 0;
    while (c2[i]) {
        c1[i] = c2[i];
        i++;
    }
    return c1;
}

char* my_scanf() {
    char c;
    int i = 0;
    char* str = (char*)calloc(6, sizeof(char)); // Free this memory later
    printf(">");
    
    while (read(0, &c, 1)) {
        if (c == '\n' || i == 5) {
            return str;
        }
        str[i] = c;
        i++;
    }

    return str;
}

void my_gameprocess(int attempts, char* secret_code) {
    int i = 0;
    char* entercode;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (i < attempts) {
        printf("Round %d\n", i);
        if (my_strcmp(entercode = my_scanf(), "stop") == 0) {
            free(entercode);
            return;
        }

        printf("%s\n", entercode);
        free(entercode);
        i++;
    }
}

void main_work(int argc, char** argv) {
    char* secret_code = (char*)calloc(5, sizeof(char));
    int attempts = 10;

    for (int i = 1; i < argc; i++) {
        if ((my_strcmp(argv[i], "-c")) == 0) {
            my_strcpy(secret_code, argv[i + 1]);
        } else if ((my_strcmp(argv[i], "-t")) == 0) {
            attempts = my_atoi(argv[i + 1]);
        }
    }

    if (!secret_code[0]) {
        my_rand(secret_code);
    }

    printf("%d\n%s\n", attempts, secret_code);
    my_gameprocess(attempts, secret_code);

    free(secret_code);
}

int main(int argc, char** argv) {
    main_work(argc, argv);
    return 0;
}
