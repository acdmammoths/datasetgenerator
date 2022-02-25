HFILES = glob.h choose.h gen.h

CFILES =  gen.c main.c command.c util.c

OBJECTS = gen.o main.o command.o util.o

LIBS = -lm

UNAME := $(shell uname)
ifeq ($(UNAME), FreeBSD)
	# Fix to use your own version of GCC
	LINKER=-Wl,-rpath=/usr/local/lib/gcc11
endif

CC = g++

#PROFILE=-pg
#GDB=-ggdb3
#DEBUG=-DDEBUG
ifndef DEBUG
	OPT=-Ofast -pipe -march=native -mtune=native #-m64
endif

# For some reasons, -static does not work on Mac OS X (MacPorts g++ 4.9) (FIXME)
STATIC=-static
ifeq ($(UNAME), Darwin)
	STATIC=-static-libgcc -static-libstdc++
endif

WARNS=-Wextra -Wall -Wshadow -Wstrict-aliasing=1 -Werror -pedantic-errors

CFLAGS=-ansi -std=c++11 -fabi-version=6 $(WARNS) $(OPT) $(STATIC) $(GDB) $(DEBUG) $(PROFILE)

EXEC = gen

.PHONY: all default clean mrproper

all: default

default: $(EXEC)

gen:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LINKER) $(LIBS) -fwhole-program -o gen

mrproper:
	-/bin/rm -f $(OBJECTS) $(EXEC)

clean:
	-/bin/rm -f $(OBJECTS)

$(OBJECTS): $(HFILES)
