#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h> 
#include <stdio.h>
#include "navigate.h"
#include "bfs_utils.h"

/*
 * Function: task1
 * Description: Executes task1 and writes the corresponding message to the output file.
 *              This function is called when the value of 'k' is greater than 0. It uses BFS
 *              to find the maximum positive energy value within |k| steps from the starting position.
 * Parameters:
 *   output_file - Pointer to the file where the result should be written.
 *   board - Pointer to the board with energy values.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 *   startRow - Starting row position (0-based index).
 *   startCol - Starting column position (0-based index).
 *   k - Maximum distance from the starting position.
 */
void task1(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k) {
    int result = 0;
    if (bfs(board, rows, cols, startRow, startCol, k, 1, &result)) {
        if (result < 0) {
            result = 0;
        }
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, k, result);
    }
}
/*
 * Function: task2
 * Description: Executes task2 and writes the corresponding message to the output file.
 *              This function is called when the value of 'k' is less than 0. It uses BFS
 *              to sum all positive energy values within |k| steps from the starting position.
 * Parameters:
 *   output_file - Pointer to the file where the result should be written.
 *   board - Pointer to the board with energy values.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 *   startRow - Starting row position (0-based index).
 *   startCol - Starting column position (0-based index).
 *   k - Maximum distance from the starting position.
 */
void task2(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k) {
    int result;
    if (bfs(board, rows, cols, startRow, startCol, k, 2, &result)) {
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, k, result);
    }
}

/**
 * @brief Executes task3 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is equal to 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task3(FILE *output_file) {
    fprintf(output_file, "Executing task3: k == 0\n");
}
