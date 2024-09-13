/*
 * File: navigate.c
 * Author: Matilde and Eduardo
 * Date: September 13, 2024
 * Description: This file contains the main function of the program, which handles navigation and processing of a board from an input file. 
 *              The program validates arguments, reads and writes files, allocates and frees memory for the board, and executes tasks based on a specific value.
 * 
 * Main Functions:
 * - main: The main function of the program that manages the flow of reading, processing, and writing data.
 */

#include "navigate.h"
#include "file_utils.h"
#include "board_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Function: main
 * Description: Main function of the program. Manages the execution of the program based on the provided arguments, processes input and output files, 
 *              allocates and deallocates memory for the board, and performs different tasks based on the value of 'k'.
 * Parameters:
 *   argc - Number of arguments passed to the program
 *   argv - Array of strings containing the program arguments
 * Return:
 *   EXIT_SUCCESS if the program executes successfully, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    int rows, cols, taskId, startRow, startCol, endRow, endCol;

    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>.1maps\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Validate the file extension
    if (!validate_extension(argv[1])) {
        fprintf(stderr, "Error: The file must have the extension %s\n", EXTENSION_MAPS);
        return EXIT_FAILURE;
    }

    // Open the input and output files
    FILE *inputFile = open_file(argv[1], "r");
    if (!inputFile) return EXIT_FAILURE;

    FILE *outputFile = create_output_file(argv[1], "sol1maps");
    if (!outputFile) {
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Read the first line of the input file
    char line[MAX_LINE_LENGTH];
    if (!read_first_line(inputFile, line, &rows, &cols, &taskId, &startRow, &startCol, &endRow, &endCol)) {
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    // Write the header to the output file
    fprintf(outputFile, "%s", line);

    // Allocate the board and read its data
    int **board = allocate_board(rows, cols);
    if (!board || !read_board(inputFile, board, rows, cols)) {
        free_board(board, rows);
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    // Write the board to the output file (for debugging purposes)
    print_board(outputFile, board, rows, cols);

    // Invoke the appropriate task function based on the value of 'taskId'
    if (taskId > 0) {
        task1(outputFile);
    } else if (taskId < 0) {
        task2(outputFile);
    } else {
        task3(outputFile);
    }

    // Free the memory allocated for the board
    free_board(board, rows);

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}