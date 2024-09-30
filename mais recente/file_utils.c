#include "file_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h> 
#include <ctype.h>
#include <sys/types.h> 
#include <stddef.h> 

#ifndef _SSIZE_T_DEFINED
typedef ptrdiff_t ssize_t;
#define _SSIZE_T_DEFINED
#endif

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    size_t pos = 0;
    int c;

    if (*lineptr == NULL) {
        *n = 128;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n * 2;
            char *new_ptr = (char *)realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *lineptr = new_ptr;
            *n = new_size;
        }
        (*lineptr)[pos++] = c;
        if (c == '\n') {
            break;
        }
    }

    if (pos == 0 && c == EOF) {
        return -1;
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

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
    free(output_filename);  // Libere a memória alocada
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_first_line(FILE *input_file, int *rows, int *cols, int *startRow, int *startCol, int *taskId, int *endRow, int *endCol) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *buffer = NULL;
    size_t buffer_size = 0;
    int parsed = 0;

    while ((read = getline(&line, &len, input_file)) != -1) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        size_t new_size = buffer_size + read + 1;
        char *new_buffer = realloc(buffer, new_size);
        if (!new_buffer) {
            free(line);
            free(buffer);
            return 0;
        }
        buffer = new_buffer;
        buffer_size = new_size;

        if (buffer_size == new_size) {
            buffer[buffer_size - read - 1] = '\0';
        }

        strncat(buffer, line, read);

        parsed = sscanf(buffer, "%d %d %d %d %d %d %d", rows, cols, startRow, startCol, taskId, endRow, endCol);

        if (parsed >= 5) {
            if (*taskId == 0 && parsed != 7) {
                free(line);
                free(buffer);
                return 0;
            }
            free(line);
            free(buffer);
            return 1;
        }
    }
    free(line);
    free(buffer);
    return 0;
}
