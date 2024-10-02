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
 *   Parameters:
 *     - rows: Number of rows in the board.
 *     - cols: Number of columns in the board.
 *   Returns:
 *     - int**: Pointer to the allocated board, or NULL if memory allocation fails.
 *
 * - free_board: Frees the memory allocated for the board.
 *   Parameters:
 *     - board: Pointer to the board to be freed.
 *     - rows: Number of rows in the board.
 *
 * - read_board: Reads board data from the input file and populates the board with the data.
 *   Parameters:
 *     - input_file: File pointer to the input file.
 *     - board: Pointer to the board to be populated.
 *     - rows: Number of rows in the board.
 *     - cols: Number of columns in the board.
 *   Returns:
 *     - int: 1 if the board was successfully read, 0 otherwise.
 *
 * - print_board: Writes the board data to the output file.
 *   Parameters:
 *     - output_file: File pointer to the output file.
 *     - board: Pointer to the board to be printed.
 *     - rows: Number of rows in the board.
 *     - cols: Number of columns in the board.
 */
 
int **allocate_board(int startRow, int startCol, int endRow, int endCol, int taskid, int *allocatedRows, int *allocatedCols);
void free_board(int **board, int rows);
int read_board_line(FILE *input_file, int *board_row, int cols);

#endif
