CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c map.c getch.c grille.c
OBJS = $(SRCS:.c=.o)

TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
