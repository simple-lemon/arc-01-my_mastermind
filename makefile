CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = main.c
SRC = $(wildcard * .c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJ)
        	$(CC) $(CFLAGC) $(OBJ) -o $(TARGET)

%.o: %.c
       $(CC) $(CFGLAS) -c $< -o $@

clean:
       rm -f $(OBJ)

fclean: clean
        rm -f $(TARGET)

re: fclean all