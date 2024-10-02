#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> 
#include <ctype.h>


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
        return NULL;
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
    size_t len = strlen(filename) + strlen(extension) + 2; 
    char *output_filename = (char *)malloc(len * sizeof(char));
    if (!output_filename) {
        return NULL;
    }

    const char *dot = strrchr(filename, '.');
    if (dot && strlen(dot) > 1) {
        snprintf(output_filename, len, "%.*s.%s", (int)(dot - filename), filename, extension);
    } else {
        snprintf(output_filename, len, "%s.%s", filename, extension);
    }

    FILE *output_file = fopen(output_filename, "w");
    free(output_filename);
    if (!output_file) {
        return NULL;
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
    size_t len = strlen(filename);
    size_t ext_len = strlen(EXTENSION_MAPS);
    return (len >= ext_len && strcmp(filename + len - ext_len, EXTENSION_MAPS) == 0);
}

/*
 * Function: read_first_line
 * Description: Reads the first line of the input file and parses the values into provided variables.
 * Parameters:
 *   input_file - File pointer to the input file
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

int read_first_line(FILE *input_file, int *rows, int *cols, int *startRow, int *startCol, int *taskId, int *endRow, int *endCol) {
    char c;
    int parsed = 0;


    while ((c = fgetc(input_file)) != EOF) {
        if (c != '\n' && c != '\r') {
            ungetc(c, input_file);
            break;
        }
    }

  
    parsed = fscanf(input_file, "%d %d %d %d %d", rows, cols, startRow, startCol, taskId);

    if (parsed == 5) {
        if (*taskId == 0) {
           
            if (fscanf(input_file, "%d %d", endRow, endCol) == 2) {
                return 1;
            }
        } else {
    
            return 1;
        }
    }

    
    return 0;
}