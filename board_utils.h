#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include <stdio.h>

/*
 * Header file for board utility functions.
 *
 * This file declares functions for managing the board in the navigation program.
 * It includes functions for allocating and freeing memory for the board,
 * reading board data from an input file, and printing the board to an output file.
 *
 * Functions declared:
 * - allocate_board: Allocates memory for a board with the specified number of rows and columns.
 * - free_board: Frees the memory allocated for the board.
 * - read_board: Reads board data from the input file and populates the board with the data.
 * - print_board: Writes the board data to the output file.
 */

int **allocate_board(int rows, int cols);
void free_board(int **board, int rows);
int read_board(FILE *input_file, int **board, int rows, int cols);
void print_board(FILE *output_file, int **board, int rows, int cols);

#endif

