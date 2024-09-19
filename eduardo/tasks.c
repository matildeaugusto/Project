#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h> 
#include <stdio.h>
#include "navigate.h"
#include "bfs_utils.h"


/* Declaração antecipada da função */
void caminhoVerticalHorizontal(int l1, int c1, int l2, int c2, FILE *output_file, int **board);

/*
 * Function: task1
 * Description: Executes task1 and writes the corresponding message to the output file.
 *              This function is called when the value of 'k' is greater than 0. It uses BFS
 *              to find the maximum positive energy value within |k| steps from the starting position.
 * Parameters:
 *   output_file - Pointer to the file where the result should be written.
 *   board - Pointer to the board with energy values.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 *   startRow - Starting row position (0-based index).
 *   startCol - Starting column position (0-based index).
 *   k - Maximum distance from the starting position.
 */
void task1(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k) {
    int result = 0;
    if (bfs(board, rows, cols, startRow, startCol, k, 1, &result)) {
        if (result < 0) {
            result = 0;
        }
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, k, result);
    }
}
/*
 * Function: task2
 * Description: Executes task2 and writes the corresponding message to the output file.
 *              This function is called when the value of 'k' is less than 0. It uses BFS
 *              to sum all positive energy values within |k| steps from the starting position.
 * Parameters:
 *   output_file - Pointer to the file where the result should be written.
 *   board - Pointer to the board with energy values.
 *   rows - Number of rows in the board.
 *   cols - Number of columns in the board.
 *   startRow - Starting row position (0-based index).
 *   startCol - Starting column position (0-based index).
 *   k - Maximum distance from the starting position.
 */
void task2(FILE *output_file, int **board, int rows, int cols, int startRow, int startCol, int k) {
    int result;
    if (bfs(board, rows, cols, startRow, startCol, k, 2, &result)) {
        fprintf(output_file, "%d %d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, k, result);
    }
}

/**
 * @brief Executes task3 and writes the corresponding message to the output file.
 *
 * This function is called when the value of 'k' is equal to 0.
 *
 * @param output_file Pointer to the file where the message should be written.
 */
void task3(FILE *output_file, int rows, int cols, int startRow, int startCol, int endRow, int endCol, int taskId, int **board) {
    // Repetir a primeira linha do problema
    fprintf(output_file, "%d %d %d %d %d %d %d\n", rows, cols, startRow + 1, startCol + 1, taskId, endRow, endCol);

    // Verificar se as coordenadas estão dentro dos limites do mapa
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols || endRow < 0 || endRow >= rows || endCol < 0 || endCol >= cols) {
        return;
    }

    // Chamar a função para mover verticalmente e horizontalmente e escrever o caminho no arquivo de saída
    caminhoVerticalHorizontal(startRow, startCol, endRow, endCol, output_file, board);
}
    
/**
 * brief Moves vertically and horizontally from (l1, c1) to (l2, c2) and writes the path to the output file.
 *
 * param l1 Starting row position.
 * param c1 Starting column position.
 * param l2 Ending row position.
 * param c2 Ending column position.
 * param output_file Pointer to the file where the path should be written.
 */
void caminhoVerticalHorizontal(int l1, int c1, int l2, int c2, FILE *output_file, int **board) {
    while (c1 != c2) {
        c1 += (c2 > c1) ? 1 : -1;
        fprintf(output_file, "%d %d %d\n", l1, c1 + 1, board[l1][c1]);
    }
    while (l1 != l2) {
        l1 += (l2 > l1) ? 1 : -1;
        fprintf(output_file, "%d, %d %d\n", l1 + 1, c1, board[l1][c1]);
    }
    
}