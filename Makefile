CC = gcc 
CFLAS = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind

$(TARGET):$(SOURCE)
	$(CC) $(CFLAS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -f $(TARGET)
