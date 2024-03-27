
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SOURCES = my_mastermind.c 
TARGET = my_mastermind

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -r $(TARGET)

fclean: clean
	@rm -f $(TARGET)