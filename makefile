CC = gcc
 CFLAGS = -Wall -Wextra -Werror
 TARGET = my_mastermind
 SRC = my_mastermind.c
 OBJ = $(SRC:.c=.o)
 
 .PHONY: all clean fclean re
 
 all: $(TARGET)
 
 $(TARGET): $(OBJ)
 	$(CC) $(CFLAGS) -o $@ $^
 
 $(OBJ): $(SRC)
 	$(CC) $(CFLAGS) -c $< -o $@
 
 clean:
 	rm -f $(OBJ)
 
 fclean: clean
 	rm -f $(TARGET)
 
 re: fclean all