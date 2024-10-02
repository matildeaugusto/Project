#include "board_utils.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Function: allocate_board
 * Description: Allocates memory for a board with the specified number of rows and columns.
 *              Returns a pointer to the allocated board, or NULL if the allocation fails.
 * Parameters:
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 * Return:
 *   int** - A pointer to the allocated board, or NULL if memory allocation fails.
 */
int **allocate_board(int startRow, int startCol, int endRow, int endCol, int taskId, int *allocatedRows, int *allocatedCols) {
    int radius = abs(taskId);

    if (taskId != 0) {
        *allocatedRows = 2 * radius + 1;
        *allocatedCols = 2 * radius + 1;
    } else {
        *allocatedRows = abs(endRow - startRow) + 1;
        *allocatedCols = abs(endCol - startCol) + 1;
    }

    if (*allocatedRows <= 0 || *allocatedCols <= 0) {
        return NULL;
    }

    int **board = (int **)malloc(*allocatedRows * sizeof(int *));
    if (!board) {
        return NULL;
    }

    for (int i = 0; i < *allocatedRows; i++) {
        board[i] = (int *)malloc(*allocatedCols * sizeof(int));
        if (!board[i]) {
            for (int j = 0; j < i; j++) {
                free(board[j]);
            }
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
 *   board - Pointer to the board to be freed.
 *   rows - Number of rows in the board.
 */
void free_board(int **board, int allocatedRows) {
    if (board == NULL) return;
    
    for (int i = 0; i < allocatedRows; i++) {
        free(board[i]);
    }
    free(board);
}

/*
 * Function: read_board
 * Description: Reads the board data from the input file and populates the board with the data.
 *              If the board cannot be read, an error message is printed.
 * Parameters:
 *   input_file - File pointer to the input file.
 *   board - Pointer to the board to be populated.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 * Return:
 *   int - 1 if the board was successfully read, 0 otherwise.
 */
int read_board_line(FILE *input_file, int *board_row, int cols) {
    if (!input_file || !board_row || cols <= 0) {
        return 0;
    }

    for (int j = 0; j < cols; j++) {
        if (fscanf(input_file, "%d", &board_row[j]) != 1) {
            return 0;
        }
    }
    return 1;
}
