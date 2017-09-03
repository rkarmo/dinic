CFLAGS=-Wall -Wextra -O0 -std=c11 -ggdb
all:
	cc dinic.c -o dinic $(CFLAGS)
