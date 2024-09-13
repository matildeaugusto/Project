#include "navigate.h"

/**
 * @brief Executes task1 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is greater than 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task1(FILE *output_file) {
    fprintf(output_file, "Executing task1: k > 0\n");
}

/**
 * @brief Executes task2 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is less than 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task2(FILE *output_file) {
    fprintf(output_file, "Executing task2: k < 0\n");
}

/**
 * @brief Executes task3 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is equal to 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task3(FILE *output_file) {
    fprintf(output_file, "Executing task3: k == 0\n");
}
