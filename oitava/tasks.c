#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h> 
#include <stdio.h>
#include "navigate.h"
#include "bfs_utils.h"
#include "board_utils.h"
#include "file_utils.h"


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
    if (bfs(board, rows, cols, startRow - 1, startCol - 1, k, 1, &result) && result < 0) {
        result = 0;
    }
    fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow, startCol, k, result);
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
    int result = 0;
    if (bfs(board, rows, cols, startRow - 1, startCol - 1, k, 2, &result)) {
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow, startCol, k, result);
    }
}


/*
 * Function: task3
 * Description: Executes task3 and writes the corresponding message to the output file.
 *              This function is called when the value of 'k' is equal to 0. It writes the 
 *              initial conditions and calculates the path from the start to the end coordinates.
 * Parameters:
 *   output_file - Pointer to the file where the message should be written.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 *   startRow - Starting row position (1-based index).
 *   startCol - Starting column position (1-based index).
 *   endRow - Ending row position (1-based index).
 *   endCol - Ending column position (1-based index).
 *   taskId - Task identifier.
 *   board - Pointer to the board with energy values.
 */
/*
 * Function: task3
 * Description: Executes task3 and writes the corresponding message to the output file.
 *              This function is called when the value of 'k' is equal to 0. It writes the 
 *              initial conditions and calculates the path from the start to the end coordinates.
 * Parameters:
 *   output_file - Pointer to the file where the message should be written.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 *   startRow - Starting row position (1-based index).
 *   startCol - Starting column position (1-based index).
 *   endRow - Ending row position (1-based index).
 *   endCol - Ending column position (1-based index).
 *   taskId - Task identifier.
 *   board - Pointer to the board with energy values.
 */
void task3(FILE *output_file, int rows, int cols, int startRow, int startCol, int endRow, int endCol, int taskId, int **board) {
   if (startRow <= 0 || startRow > rows || startCol <= 0 || startCol > cols || endRow <= 0 || endRow > rows || endCol <= 0 || endCol > cols) {
        return;
    }
   
   
    fprintf(output_file, "%d %d %d %d %d %d %d\n", rows, cols, startRow, startCol, taskId, endRow, endCol);
    


    startRow--; 
    startCol--; 
    endRow--; 
    endCol--;

    while (startRow != endRow) {
        startRow += (startRow > endRow) ? -1 : 1;
         if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
            return;
        }
        fprintf(output_file, "%d %d %d\n", startRow + 1, startCol + 1, board[startRow][startCol]);
    }
    while (startCol != endCol) {
        startCol += (startCol > endCol) ? -1 : 1;
         if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
            return;
        }
        fprintf(output_file, "%d %d %d\n", startRow + 1, startCol + 1, board[startRow][startCol]);
    }
}
