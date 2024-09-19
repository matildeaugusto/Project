#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <stdio.h>

#define MAX_LINE_LENGTH 256
#define EXTENSION_MAPS ".1maps"

/*
 * Header file for the navigation module.
 *
 * This file declares functions and macros used for handling
 * file operations and tasks related to the navigation program.
 * It includes function declarations for file validation,
 * file opening, and task execution based on the provided
 * arguments in the main function.
 *
 * Macros:
 * - MAX_LINE_LENGTH: Maximum length of a line to be read from files.
 * - EXTENSION_MAPS: Expected file extension for input map files.
 *
 * Functions:
 * - validate_extension: Checks if the filename ends with the specified extension.
 *   Parameters:
 *     - filename: The name of the file to check.
 *   Returns:
 *     - 1 if the filename has the correct extension, 0 otherwise.
 *
 * - open_file: Opens a file with the given filename and mode.
 *   Parameters:
 *     - filename: The name of the file to open.
 *     - mode: The mode in which to open the file (e.g., "r" for reading).
 *   Returns:
 *     - A pointer to the opened file, or NULL if the file could not be opened.
 *
 * - main: Main function that controls program execution.
 *   Parameters:
 *     - argc: Number of arguments passed to the program.
 *     - argv: Array of strings containing the program arguments.
 *   Returns:
 *     - EXIT_SUCCESS if the program executes successfully, EXIT_FAILURE otherwise.
 *
 * - task1: Executes task1 and writes the result to the output file.
 *   Parameters:
 *     - output_file: The file to write the result to.
 *     - board: 2D array representing the board.
 *     - rows: Number of rows in the board.
 *     - cols: Number of columns in the board.
 *     - startRow: Starting row index.
 *     - startCol: Starting column index.
 *     - k: Distance parameter for task1.
 *
 * - task2: Executes task2 and writes the result to the output file.
 *   Parameters:
 *     - output_file: The file to write the result to.
 *     - board: 2D array representing the board.
 *     - rows: Number of rows in the board.
 *     - cols: Number of columns in the board.
 *     - startRow: Starting row index.
 *     - startCol: Starting column index.
 *     - k: Distance parameter for task2.
 *
 * - task3: Executes task3 and writes the result to the output file.
 *   Parameters:
 *     - output_file: The file to write the result to.
 *   Declaração da função write_header
 */

int validate_extension(const char *filename);
FILE *open_file(const char *filename, const char *mode);
int main(int argc, char *argv[]);
void task1(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k);
void task2(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k);
void task3(FILE *output_file, int rows, int cols, int startRow, int startCol, int endRow, int endCol, int taskId, int **board);
void write_header(FILE *output_file, int rows, int cols, int startRow, int startCol, int k);

#endif
