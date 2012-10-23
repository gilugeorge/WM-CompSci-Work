CC=gcc
CFLAGS=-g -Wall -DDEBUG

all: BS bs

BS: BS.o msg.o
	gcc -o BS BS.o msg.o

bs: bs.o msg.o child.o child.h
	gcc -o bs bs.o msg.o child.o -lm

BS.o: BS.c common.h

msg.o: msg.c common.h

bs.o: bs.c common.h

child.o: child.h

clean:
	rm -f BS bs *.o serverloc
