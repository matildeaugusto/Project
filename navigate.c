#include "navigate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Main function of the program.
 *
 * This function handles the command-line arguments, validates the file extension,
 * opens the input and output files, processes the first line of the input file, 
 * and invokes the appropriate task function based on the value of 'k'.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return EXIT_SUCCESS if the program completes successfully, 
 *         EXIT_FAILURE if an error occurs.
 */
int main(int argc, char *argv[]) {
  int L, C, k, l1, c1, l2, c2;

  // Check if the correct number of arguments is provided
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>.1maps\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Validate the file extension
  if (!valida_extensao(argv[1])) {
    fprintf(stderr, "Error: The file must have the extension %s\n", EXTENSAO_MAPS);
    return EXIT_FAILURE;
  }

  // Open the input file for reading
  FILE *input_file = abre_arquivo(argv[1], "r");
  if (!input_file) return EXIT_FAILURE;

  // Generate the name of the output file
  char output_filename[MAX_LINE_LENGTH];
  strncpy(output_filename, argv[1], strlen(argv[1]) - 6);
  strcat(output_filename, ".sol1maps");

  // Open the output file for writing
  FILE *output_file = abre_arquivo(output_filename, "w");
  if (!output_file) {
    fclose(input_file);
    return EXIT_FAILURE;
  }

  // Read the first line from the input file
  char line[MAX_LINE_LENGTH];
  if (fgets(line, sizeof(line), input_file)) {
    // Parse the values from the first line
    int num_values = sscanf(line, "%d %d %d %d %d %d %d", &L, &C, &k, &l1, &c1, &l2, &c2);
    fprintf(output_file, "%s\n", line);

      // Invoke the appropriate task function based on the value of 'k'
    if (k > 0) {
      task1(output_file);
    } else if (k < 0) {
      task2(output_file);
    } else {
      task3(output_file);
    }
  }

  // Close the files
  fclose(input_file);
  fclose(output_file);
  return EXIT_SUCCESS;
}

/**
 * @brief Validates if the given filename has the correct extension.
 *
 * @param filename The name of the file to check.
 * @return 1 if the filename has the extension ".1maps", 0 otherwise.
 */
int valida_extensao(const char *filename) {
    return (strlen(filename) >= 6 && strcmp(filename + strlen(filename) - 6, EXTENSAO_MAPS) == 0);
}

/**
 * @brief Opens a file with the specified mode.
 *
 * @param filename The name of the file to open.
 * @param mode The mode in which to open the file (e.g., "r", "w").
 * @return Pointer to the opened file, or NULL if the file cannot be opened.
 */
FILE *abre_arquivo(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (!file) {
    perror("Error opening file");
  }
  return file;
}
