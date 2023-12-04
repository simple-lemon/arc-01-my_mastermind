CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all
