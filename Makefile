CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = my_mastermind
SOURCES = my_mastermind.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean fclean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)
