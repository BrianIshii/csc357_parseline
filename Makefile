FLAGS=-Wall -g -Werror -lm -pedantic -std=gnu99
SRC=parselineFuncs.c parseline.c
OBJS=parselineFuncs.o parseline.o parseline.h
CC=gcc

all: parseline

parseline: $(OBJS)
	$(CC) -o parseline $(OBJS) $(FLAGS)

parseline.o: parseline.c
	$(CC) -c parseline.c $(FLAGS)

parselineFuncs.o: parselineFuncs.c
	$(CC) -c parselineFuncs.c $(FLAGS)

test:
	./test.sh
	
clean:
	make 
	rm parseline.o
	rm parselineFuncs.o
