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
 * Functions declared:
 * - validate_extension: Checks if the filename ends with the specified extension.
 * - open_file: Opens a file with the given filename and mode.
 * - main: Main function that controls program execution.
 * - task1: Executes task1 and writes the corresponding message to the output file.
 * - task2: Executes task2 and writes the corresponding message to the output file.
 * - task3: Executes task3 and writes the corresponding message to the output file.
 */

int validate_extension(const char *filename);
FILE *open_file(const char *filename, const char *mode);
int main(int argc, char *argv[]);
void task1(FILE *output_file);
void task2(FILE *output_file);
void task3(FILE *output_file);

#endif
