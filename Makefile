CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): my_mastermind.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
	del $(TARGET).exe

.PHONY: all clean