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
    fprintf(stderr, "Error opening file %s with mode %s: %s\n", filename, mode, strerror(errno));
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
  const char *dot = strrchr(filename, '.');
  if (dot && strlen(dot) > 1) {  
    snprintf(output_filename, sizeof(output_filename), "%.*s.%s", (int)(dot - filename), filename, extension);
  } else {
    snprintf(output_filename, sizeof(output_filename), "%s.%s", filename, extension);
  }

  FILE *output_file = fopen(output_filename, "w");
  if (!output_file) {
    fprintf(stderr, "Error creating output file %s: %s\n", output_filename, strerror(errno));
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
int read_first_line(FILE *input_file, char *line, int *rows, int *cols, int *startRow, int *startCol, int *taskId, int *endRow, int *endCol) {
    char buffer[MAX_LINE_LENGTH] = {0};
    int parsed = 0;

    while (fgets(line, MAX_LINE_LENGTH, input_file)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

         if (strlen(buffer) + strlen(line) < MAX_LINE_LENGTH) {
            strcat(buffer, line);
        } else {
            fprintf(stderr, "Error: Buffer overflow while reading the first line\n");
            return 0;
        }

        // Try to parse the concatenated buffer
        parsed = sscanf(buffer, "%d %d %d %d %d %d %d", rows, cols, startRow, startCol, taskId, endRow, endCol);

        if (parsed >= 5) {
            if (*taskId == 0 && parsed != 7) {
                return 0;  
            }
            return 1;  
       } 
  }
  return 0;  
}