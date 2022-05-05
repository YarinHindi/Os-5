CC = gcc
C = -c
O = -o
Flag = -Wall -g -c

all: server client

server: Stack.o Queue.o server.cpp
	$(CC) server.cpp -lpthread $(O) server

client: client.cpp
	$(CC) client.cpp -lpthread $(O) client

Stack.o: heap.o Node.o Stack.c
	$(CC) $(Flag)  Stack.c

Queue.o: heap.o Node.o Queue.c
	$(CC) $(Flag)  Queue.c

heap.o :heap.c
	$(CC) $(Flag)  heap.c

Node.o:	Node.c
	$(CC) $(Flag)  Node.c

.PHONY: clean all

clean:
	rm -f *.o server client