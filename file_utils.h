#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

#define MAX_LINE_LENGTH 256
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
 * - create_output_file: Creates an output file with a new filename based on the original filename and extension.
 * - validate_extension: Checks if the filename ends with the specified extension.
 * - read_first_line: Reads the first line of the input file and parses values into provided variables.
 */

FILE *open_file(const char *filename, const char *mode);
FILE *create_output_file(const char *filename, const char *extension);
int validate_extension(const char *filename);
int read_first_line(FILE *input_file, char *line, int *rows, int *cols, int *taskId, int *startRow, int *startCol, int *endRow, int *endCol);

#endif
