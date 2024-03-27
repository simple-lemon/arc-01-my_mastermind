SRC = my_mastermind.c
TARGET = my_mastermind
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^  
.PHONY:  fclean
fclean:
	rm -rf $(TARGET)
re: fclea