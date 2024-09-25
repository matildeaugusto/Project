#include "navigate.h"
#include "file_utils.h"
#include "board_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Function: write_header
 * Description: Writes the header information to the output file.
 * Parameters:
 *   output_file - Pointer to the output file
 *   rows - Number of rows in the board
 *   cols - Number of columns in the board
 *   startRow - Starting row for navigation
 *   startCol - Starting column for navigation
 *   k - A specific value for navigation
 */
void write_header(FILE *output_file, int rows, int cols, int startRow, int startCol, int k) {
    fprintf(output_file, "%d %d %d %d %d\n", rows, cols, startRow, startCol, k);
}
void write_header3(FILE *output_file, int rows, int cols, int startRow, int startCol, int k, int endRow, int endCol) {
    fprintf(output_file, "%d %d %d %d %d %d %d\n", rows, cols, startRow, startCol, k, endRow, endCol);
}

/*
 * File: navigate.c
 * Author: Matilde and Eduardo
 * Date: September 25, 2024
 * Description: This file contains the main function of the program, which handles navigation and processing of a board from an input file. 
 *              The program validates arguments, reads and writes files, allocates and frees memory for the board, and executes tasks based on a specific value.
 */

int main(int argc, char *argv[]) {
  int rows, cols, startRow, startCol, taskId;
  int endRow = 0;
  int endCol = 0;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>.1maps\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (!validate_extension(argv[1])) {
    fprintf(stderr, "Error: The file must have the extension %s\n", EXTENSION_MAPS);
    return EXIT_FAILURE;
  }

  FILE *inputFile = open_file(argv[1], "r");
  if (!inputFile) {
    fprintf(stderr, "Error: Could not open input file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  FILE *outputFile = create_output_file(argv[1], "sol1maps");
  if (!outputFile) {
    fprintf(stderr, "Error: Could not create output file\n");
    fclose(inputFile);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH];
  
  while (read_first_line(inputFile, line, &rows, &cols, &startRow, &startCol, &taskId, &endRow, &endCol)) {
    if (taskId != 0 ) {
    if (startRow <= 0 || startRow > rows || startCol <= 0 || startCol > cols) {
      write_header(outputFile, rows, cols, startRow, startCol, taskId);
      fprintf(stderr, "Warning: Start coordinates (%d, %d) are out of bounds for a %dx%d board.\n", startRow, startCol, rows, cols);
      
      for (int i = 0; i < rows; i++) {
        if (fgets(line, MAX_LINE_LENGTH, inputFile) == NULL) {
          fprintf(stderr, "Error: Failed to read line from input file while skipping board data.\n");
          break;  
        }
      }

      fprintf(outputFile, "\n");
      continue;  
    }
    } else {
      if (startRow <= 0 || startRow > rows || startCol <= 0 || startCol > cols || endRow > rows || endCol > cols || endRow < 0|| endCol <= 0) {
      write_header3(outputFile, rows, cols, startRow, startCol, taskId, endRow, endCol);
      
      
      for (int i = 0; i < rows; i++) {
        if (fgets(line, MAX_LINE_LENGTH, inputFile) == NULL) {
          fprintf(stderr, "Error: Failed to read line from input file while skipping board data.\n");
          break;  
        }
      }

      fprintf(outputFile, "\n");
      continue;  
    }

    }

    int **board = allocate_board(rows, cols);
    if (!board) { 
      fprintf(stderr, "Error: Failed to allocate memory for the board\n");
      fclose(inputFile);
      fclose(outputFile);
      return EXIT_FAILURE;
    }

    if (!read_board(inputFile, board, rows, cols)) {
      fprintf(stderr, "Error: Failed to read the board data\n");
      free_board(board, rows);
      fclose(inputFile);
      fclose(outputFile);
      return EXIT_FAILURE;
    }

    if (taskId < 0) {
      task1(outputFile, board, rows, cols, startRow, startCol, taskId);
    } else if (taskId > 0) {
      task2(outputFile, board, rows, cols, startRow, startCol, taskId);
    } else {
      task3(outputFile, rows, cols, startRow, startCol, endRow, endCol, taskId, board);
    }

    free_board(board, rows);
    fprintf(outputFile, "\n");
  }

  fclose(inputFile);
  fclose(outputFile);

  
}
