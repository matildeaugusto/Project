# Makefile

# Variáveis
CC = gcc
CFLAGS = -Wall -std=c99 -O3


# Regras
all: navigate

navigate: scan_board.o board_utils.o file_utils.o navigate.o tasks.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o navigate scan_board.o board_utils.o file_utils.o navigate.o tasks.o

scan_board.o: scan_board.c scan_board.h
	$(CC) $(CFLAGS) -c scan_board.c

board_utils.o: board_utils.c board_utils.h
	$(CC) $(CFLAGS) -c board_utils.c

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

navigate.o: navigate.c navigate.h
	$(CC) $(CFLAGS) -c navigate.c

tasks.o: tasks.c
	$(CC) $(CFLAGS) -c tasks.c

clean:
	rm -f navigate scan_board.o board_utils.o file_utils.o navigate.o tasks.o

