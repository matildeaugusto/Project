# Makefile

# Variáveis
CC = gcc
CFLAGS = -Wall -std=c99 -g

# Regras
all: navigate

navigate: bfs_utils.o board_utils.o file_utils.o navigate.o tasks.o
	$(CC) $(CFLAGS) -o navigate bfs_utils.o board_utils.o file_utils.o navigate.o tasks.o

bfs_utils.o: bfs_utils.c bfs_utils.h
	$(CC) $(CFLAGS) -c bfs_utils.c

board_utils.o: board_utils.c board_utils.h
	$(CC) $(CFLAGS) -c board_utils.c

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

navigate.o: navigate.c navigate.h
	$(CC) $(CFLAGS) -c navigate.c

tasks.o: tasks.c
	$(CC) $(CFLAGS) -c tasks.c

clean:
	rm -f navigate bfs_utils.o board_utils.o file_utils.o navigate.o tasks.o
