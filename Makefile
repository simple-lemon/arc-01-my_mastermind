CC = gcc 
GCFLC = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind

$(TARGET): $(SOURCE)
	$(CC) $(GCFLC) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)