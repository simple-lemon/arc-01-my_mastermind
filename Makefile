CC = gcc
CFCLS = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET =  my_mastermind

$(TARGET): $(SOURCE)
	$(CC) $(CFCLS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)
