CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SOURCES = my_mastermind.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY:fclean

fclean:
	rm -rf $(TARGET)