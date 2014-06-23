HFILES = glob.h choose.h gen.h

CFILES =  gen.c main.c command.c util.c

OBJECTS = gen.o main.o command.o util.o

LIBS = -lm
CC = g++-4.9
CFLAGS = -ansi -std=c++11 -fabi-version=6 -Ofast -pipe -march=native -mtune=native -Wextra -Wall -Wshadow -Wstrict-aliasing=1 -Werror -pedantic-errors

EXEC = gen 

.PHONY: default clean mrproper

default: $(EXEC)

gen:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o gen

test:	$(OBJECTS) test.o
	$(CC) $(CFLAGS) $(OBJECTS) test.o $(LIBS) -o test

mrproper:
	-/bin/rm -f $(OBJECTS) $(EXEC)

clean:
	-/bin/rm -f $(OBJECTS) 

$(OBJECTS): $(HFILES)

