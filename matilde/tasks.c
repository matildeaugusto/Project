#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h> 
#include <stdio.h>
#include "navigate.h"
#include "bfs_utils.h"

/**
 * @brief Executes task1 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is greater than 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task1(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k) {
    int result;
    if (bfs(board, rows, cols, startRow, startCol, k, 1, &result)) {
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, k, startRow + 1, startCol + 1, result);
    }
}

/**
 * @brief Executes task2 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is less than 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task2(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k) {
    int result;
    if (bfs(board, rows, cols, startRow, startCol, k, 2, &result)) {
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, k, startRow + 1, startCol + 1, result);
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
