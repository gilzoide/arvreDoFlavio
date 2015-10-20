objs = main.o arvore.o abb.c
exe = main

CC = gcc
CFLAGS = -Wall -g

all : $(objs)
	$(CC) $(CFLAGS) -o $(exe) $^

run :
	@./$(exe)

clean :
	$(RM) $(objs) *~ $(exe)
