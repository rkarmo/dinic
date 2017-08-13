CFLAGS=-Wall -Wextra -O0 -std=c11
all:
	cc dinic.c -o dinic $(CFLAGS)
