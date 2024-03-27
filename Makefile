CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = my_mastermind.c
OBJS = $(SRCS:.c=.o)
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all