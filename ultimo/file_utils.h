#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>


#define MAX_LINE_LENGTH 10000
#define EXTENSION_MAPS ".1maps"  

/*
 * Header file for file utility functions.
 *
 * This file declares functions and macros for handling file operations
 * in the navigation program. It includes functions for opening files,
 * creating output files with specific extensions, validating file extensions,
 * and reading the first line of the input file.
 *
 * Functions declared:
 * - open_file: Opens a file with the given filename and mode.
 *   Parameters:
 *     - filename: Name of the file to open.
 *     - mode: Mode in which to open the file (e.g., "r", "w").
 *   Returns:
 *     - FILE*: A pointer to the opened file, or NULL if the file could not be opened.
 *
 * - create_output_file: Creates an output file with a new filename based on the original filename and extension.
 *   Parameters:
 *     - filename: Name of the original file.
 *     - extension: Extension for the new output file.
 *   Returns:
 *     - FILE*: A pointer to the created output file, or NULL if the file could not be created.
 *
 * - validate_extension: Checks if the filename ends with the specified extension.
 *   Parameters:
 *     - filename: Name of the file to check.
 *   Returns:
 *     - int: 1 if the file has the correct extension, 0 otherwise.
 *
 * - read_first_line: Reads the first line of the input file and parses values into provided variables.
 *   Parameters:
 *     - input_file: File pointer to the input file.
 *     - line: Buffer to store the read line.
 *     - rows: Pointer to store the number of rows.
 *     - cols: Pointer to store the number of columns.
 *     - taskId: Pointer to store the task ID.
 *     - startRow: Pointer to store the starting row.
 *     - startCol: Pointer to store the starting column.
 *     - endRow: Pointer to store the ending row.
 *     - endCol: Pointer to store the ending column.
 *   Returns:
 *     - int: 1 if the line was successfully read and parsed, 0 otherwise.
 */

FILE *open_file(const char *filename, const char *mode);
FILE *create_output_file(const char *filename, const char *extension);
int validate_extension(const char *filename);
int read_first_line(FILE *input_file, int *rows, int *cols, int *startRow, int *startCol, int *taskId, int *endRow, int *endCol);

#endif // FILE_UTILS_H