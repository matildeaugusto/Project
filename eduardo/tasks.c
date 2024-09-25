#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h> 
#include <stdio.h>
#include "navigate.h"
#include "bfs_utils.h"
#include "board_utils.h"
#include "file_utils.h"

void caminhoVerticalHorizontal(int l1, int c1, int l2, int c2, FILE *output_file, int **board, int minRow, int minCol);

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
  startRow--;
  startCol--;
  int result = 0;

  // Determine the bounds of the submatrix
  int minRow = (startRow - k < 0) ? 0 : startRow - k;
  int maxRow = (startRow + k >= rows) ? rows - 1 : startRow + k;
  int minCol = (startCol - k < 0) ? 0 : startCol - k;
  int maxCol = (startCol + k >= cols) ? cols - 1 : startCol + k;

  // Allocate the submatrix
  int subRows = maxRow - minRow + 1;
  int subCols = maxCol - minCol + 1;
  int **subBoard = allocate_board(subRows, subCols);

  // Copy the relevant part of the board to the submatrix
  for (int i = minRow; i <= maxRow; i++) {
    for (int j = minCol; j <= maxCol; j++) {
      subBoard[i - minRow][j - minCol] = board[i][j];
    }
  }

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
  startRow--;
  startCol--;
  int result;
  // Determine the bounds of the submatrix
  int minRow = (startRow - abs(k) < 0) ? 0 : startRow - abs(k);
  int maxRow = (startRow + abs(k) >= rows) ? rows - 1 : startRow + abs(k);
  int minCol = (startCol - abs(k) < 0) ? 0 : startCol - abs(k);
  int maxCol = (startCol + abs(k) >= cols) ? cols - 1 : startCol + abs(k);

  // Allocate the submatrix
  int subRows = maxRow - minRow + 1;
  int subCols = maxCol - minCol + 1;
  int **subBoard = allocate_board(subRows, subCols);

  // Copy the relevant part of the board to the submatrix
  for (int i = minRow; i <= maxRow; i++) {
    for (int j = minCol; j <= maxCol; j++) {
      subBoard[i - minRow][j - minCol] = board[i][j];
    }
  }

  if (bfs(subBoard, subRows, subCols, startRow - minRow, startCol - minCol, k, 2, &result)) {
    fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, k, result);
  }

  free_board(subBoard, subRows);
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
void task3(FILE *output_file, int rows, int cols, int startRow, int startCol, int endRow, int endCol, int taskId, int **board) {
  fprintf(output_file, "%d %d %d %d %d %d %d\n", rows, cols, startRow, startCol, taskId, endRow, endCol);

  int minRow = (startRow < endRow) ? startRow : endRow;
  int maxRow = (startRow > endRow) ? startRow : endRow;
  int minCol = (startCol < endCol) ? startCol : endCol;
  int maxCol = (startCol > endCol) ? startCol : endCol;

  int subRows = maxRow - minRow + 1;
  int subCols = maxCol - minCol + 1;
  int **subBoard = allocate_board(subRows, subCols);

  // Copy the relevant part of the board to the subBoard
  for (int i = minRow; i <= maxRow; i++) {
    for (int j = minCol; j <= maxCol; j++) {
      subBoard[i - minRow][j - minCol] = board[i - 1][j - 1];
    }
  }

  caminhoVerticalHorizontal(startRow, startCol, endRow, endCol, output_file, subBoard, minRow, minCol);

  free_board(subBoard, subRows);
}

/*
 * Function: caminhoVerticalHorizontal
 * Description: Moves vertically and horizontally from (l1, c1) to (l2, c2) and writes the path to the output file.
 * Parameters:
 *   l1 - Starting row position.
 *   c1 - Starting column position.
 *   l2 - Ending row position.
 *   c2 - Ending column position.
 *   output_file - Pointer to the file where the path should be written.
 *   board - Pointer to the board with energy values.
 */
void caminhoVerticalHorizontal(int l1, int c1, int l2, int c2, FILE *output_file, int **board, int minRow, int minCol) {
  while (l1 != l2) {
    if (l1 > l2) {
      l1--;
    } else {
      l1++;
    }
    fprintf(output_file, "%d %d %d\n", l1, c1, board[l1 - minRow][c1 - minCol]);
  }

  while (c1 != c2) {
    if (c1 > c2) {
      c1--;
    } else {
      c1++;
    }
    fprintf(output_file, "%d %d %d\n", l1, c1, board[l1 - minRow][c1 - minCol]);
  }
}