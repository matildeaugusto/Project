#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "bfs_utils.h"

/**
 * @brief Performs BFS on the board to compute values based on task requirements.
 *
 * This function performs a BFS traversal on the board starting from (startRow, startCol)
 * and updates either maxEnergy or totalSum based on the provided taskType.
 *
 * @param board - Pointer to the board with energy values.
 * @param rows - Number of rows in the board.
 * @param cols - Number of columns in the board.
 * @param startRow - Starting row position (0-based index).
 * @param startCol - Starting column position (0-based index).
 * @param k - Maximum distance from the starting position.
 * @param taskType - Type of task (1 or 2) to determine the result calculation.
 * @param result - Pointer to store the result (maxEnergy or totalSum).
 * @return int - 1 if successful, 0 otherwise.
 */
int bfs(int **board, int rows, int cols, int startRow, int startCol, int k, int taskType, int *result) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int queue[rows * cols][3];
    int front = 0, back = 0;
    
    bool visited[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
        }
    }
    
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        return 0;
    }
    
    queue[back][0] = startRow;
    queue[back][1] = startCol;
    queue[back][2] = 0; // Distance from the start position
    back++;
    visited[startRow][startCol] = true;
    
    if (taskType == 1) {
        int maxEnergy = INT_MIN;
        while (front < back) {
            int currentRow = queue[front][0];
            int currentCol = queue[front][1];
            int currentDistance = queue[front][2];
            front++;
            
            if (board[currentRow][currentCol] > 0) {
                if (board[currentRow][currentCol] > maxEnergy) {
                    maxEnergy = board[currentRow][currentCol];
                }
            }
            
            if (currentDistance < abs(k)) {
                for (int d = 0; d < 4; d++) {
                    int newRow = currentRow + directions[d][0];
                    int newCol = currentCol + directions[d][1];
                    
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]) {
                        queue[back][0] = newRow;
                        queue[back][1] = newCol;
                        queue[back][2] = currentDistance + 1;
                        back++;
                        visited[newRow][newCol] = true;
                    }
                }
            }
        }
        *result = maxEnergy;
    } else if (taskType == 2) {
        int totalSum = 0;
        while (front < back) {
            int currentRow = queue[front][0];
            int currentCol = queue[front][1];
            int currentDistance = queue[front][2];
            front++;
            
            if (currentRow != startRow || currentCol != startCol) {
                if (board[currentRow][currentCol] > 0) {
                totalSum += board[currentRow][currentCol];
            }
            }
            
            if (currentDistance < abs(k)) {
                for (int d = 0; d < 4; d++) {
                    int newRow = currentRow + directions[d][0];
                    int newCol = currentCol + directions[d][1];
                    
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]) {
                        queue[back][0] = newRow;
                        queue[back][1] = newCol;
                        queue[back][2] = currentDistance + 1;
                        back++;
                        visited[newRow][newCol] = true;
                    }
                }
            }
        }
        *result = totalSum;

    }   else if (taskType == 3){
        / Função para a Tarefa #3
void caminhoVerticalHorizontal(int l1, int c1, int l2, int c2, FILE *saida) {
    while (l1 != l2) {
        l1 += (l2 > l1) ? 1 : -1;
        fprintf(saida, "(%d, %d)\n", l1, c1);
    }
    while (c1 != c2) {
        c1 += (c2 > c1) ? 1 : -1;
        fprintf(saida, "(%d, %d)\n", l1, c1);
    }

    }}
    
    return 1;
}
