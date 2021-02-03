CC             = gcc
CFLAGS         = -Wall -g -O2 -std=c99

all: main

main: ringBuffer.c main.c
	$(CC) $(CFLAGS) -o main main.c ringBuffer.c

clean:
	rm -f main