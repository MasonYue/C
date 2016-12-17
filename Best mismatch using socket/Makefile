CC = gcc
CFLAGS = -Wall -std=c99 -g
PORT = 57988
CFLAGS += -DPORT=\$(PORT)

all: mismatch_server

mismatch_server: qtree.c questions.c utils.c categorizer.c
	$(CC) $(CFLAGS) qtree.c questions.c categorizer.c utils.c -o mismatch_server

clean:
	rm mismatch_server
