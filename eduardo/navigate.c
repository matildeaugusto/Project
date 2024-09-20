#include "navigate.h"
#include "file_utils.h"
#include "board_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void write_header(FILE *output_file, int rows, int cols, int startRow, int startCol, int k) {
    fprintf(output_file, "%d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, k);
}


/*
 * File: navigate.c
 * Author: Matilde and Eduardo
 * Date: September 17, 2024
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
        startCol--;
        startRow--;

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

         if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
            write_header(outputFile, rows, cols, startRow, startCol, taskId);
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

    return EXIT_SUCCESS;
}


    