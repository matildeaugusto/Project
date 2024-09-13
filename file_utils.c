#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Function: open_file
 * Description: Opens a file with the specified filename and mode. If the file cannot be opened, prints an error message.
 * Parameters:
 *   filename - Name of the file to open
 *   mode - Mode in which to open the file (e.g., "r", "w")
 * Return:
 *   FILE* - A pointer to the opened file, or NULL if the file could not be opened
 */
FILE *open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        perror("Error opening file");
    }
    return file;
}

/*
 * Function: create_output_file
 * Description: Creates an output file with a new filename based on the original filename and a specified extension. 
 *              If the file cannot be created, prints an error message.
 * Parameters:
 *   filename - Name of the original file
 *   extension - Extension for the new output file
 * Return:
 *   FILE* - A pointer to the created output file, or NULL if the file could not be created
 */
FILE *create_output_file(const char *filename, const char *extension) {
    char output_filename[MAX_LINE_LENGTH];
    snprintf(output_filename, sizeof(output_filename), "%.*s.%s", (int)(strlen(filename) - 6), filename, extension);

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Error creating output file");
    }
    return output_file;
}

/*
 * Function: validate_extension
 * Description: Checks if the given filename ends with the specified extension.
 * Parameters:
 *   filename - Name of the file to check
 * Return:
 *   int - 1 if the file has the correct extension, 0 otherwise
 */
int validate_extension(const char *filename) {
    return (strlen(filename) >= 6 && strcmp(filename + strlen(filename) - 6, EXTENSION_MAPS) == 0);
}

/*
 * Function: read_first_line
 * Description: Reads the first line of the input file and parses the values into provided variables.
 * Parameters:
 *   input_file - File pointer to the input file
 *   line - Buffer to store the read line
 *   rows - Pointer to store the number of rows
 *   cols - Pointer to store the number of columns
 *   taskId - Pointer to store the task ID
 *   startRow - Pointer to store the starting row
 *   startCol - Pointer to store the starting column
 *   endRow - Pointer to store the ending row
 *   endCol - Pointer to store the ending column
 * Return:
 *   int - 1 if the line was successfully read and parsed, 0 otherwise
 */
int read_first_line(FILE *input_file, char *line, int *rows, int *cols, int *taskId, int *startRow, int *startCol, int *endRow, int *endCol) {
    if (fgets(line, MAX_LINE_LENGTH, input_file)) {
        return sscanf(line, "%d %d %d %d %d %d %d", rows, cols, taskId, startRow, startCol, endRow, endCol) == 7;
    }
    fprintf(stderr, "Error: Could not read the first line of the file\n");
    return 0;
}
