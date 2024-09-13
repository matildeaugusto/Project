#include "board_utils.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Function: allocate_board
 * Description: Allocates memory for a board with specified number of rows and columns. Returns a pointer to the allocated board, or NULL if allocation fails.
 * Parameters:
 *   rows - Number of rows in the board
 *   cols - Number of columns in the board
 * Return:
 *   int** - A pointer to the allocated board, or NULL if memory allocation fails
 */
int **allocate_board(int rows, int cols) {
    int **board = (int **)malloc(rows * sizeof(int *));
    if (!board) return NULL;
    for (int i = 0; i < rows; i++) {
        board[i] = (int *)malloc(cols * sizeof(int));
        if (!board[i]) {
            for (int j = 0; j < i; j++) free(board[j]);
            free(board);
            return NULL;
        }
    }
    return board;
}

/*
 * Function: free_board
 * Description: Frees the memory allocated for the board.
 * Parameters:
 *   board - Pointer to the board to be freed
 *   rows - Number of rows in the board
 */
void free_board(int **board, int rows) {
    for (int i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
}

/*
 * Function: read_board
 * Description: Reads the board data from the input file and populates the board with the data.
 * Parameters:
 *   input_file - File pointer to the input file
 *   board - Pointer to the board to be populated
 *   rows - Number of rows in the board
 *   cols - Number of columns in the board
 * Return:
 *   int - 1 if the board was successfully read, 0 otherwise
 */
int read_board(FILE *input_file, int **board, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(input_file, "%d", &board[i][j]) != 1) {
                fprintf(stderr, "Error: Failed to read board data\n");
                return 0;
            }
        }
    }
    return 1;
}

/*
 * Function: print_board
 * Description: Writes the board data to the output file. Each row of the board is written on a new line.
 * Parameters:
 *   output_file - File pointer to the output file
 *   board - Pointer to the board to be printed
 *   rows - Number of rows in the board
 *   cols - Number of columns in the board
 */
void print_board(FILE *output_file, int **board, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(output_file, "%d ", board[i][j]);
        }
        fprintf(output_file, "\n");
    }
}
