CC = gcc
CFLAGS = -Wall -g
objs = main.o matriz.o
exe = saida

all : $(objs)
	$(CC) $^ $(CFLAGS) -o $(exe)

run :
	@./$(exe)

clean :
	$(RM) *.o *~ $(exe)
