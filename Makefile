CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = my_mastermind
SRCS = my_mastermind.c
OBJS = $(SRCS:.c=.0)

.PHONY: all clear fclear re

all: $(TARGET)

$(TARGET0): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	rm -f $(TARGET)

fclear: clear
	rm -f $(TARGET)

re: fclear all