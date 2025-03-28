.PHONY: all clean re

EXEC = game
RM = rm -f
CC = gcc

CCFLAGS = -Wall -MMD -MP -Ipackage
LDFLAGS = -lm

SRC = $(wildcard *.c */*.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

-include $(DEP)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP) $(EXEC)

re: clean all
