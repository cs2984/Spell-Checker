# Makefile
# Problem Set 5 Part II - spell checker
#

CC      = gcc
CFLAGS  = -g -std=c99 -Wall

EXE  = speller

SRCS = speller.c dictionary.c
OBJS = $(SRCS:.c=.o)
HDRS = dictionary.h

$(EXE): $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f *~ core $(EXE) *.o
	rm -rf *.dSYM
