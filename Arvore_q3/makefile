objs = main.o arvore.o eqPolonesa.o
exe = main

CC = gcc
CFLAGS = -Wall -g

all : $(objs)
	$(CC) $(CFLAGS) -o $(exe) $^

run :
	@./$(exe)


.PHONY : clean zip
zip :
	zip q3 *.c *.h makefile

clean :
	$(RM) $(objs) *~ $(exe)
