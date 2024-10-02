#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "scan_board.h"


int scan_board(int **board, int rows, int cols, int startRow, int startCol, int k, int taskType, int *result) {
    int maxEnergy = INT_MIN;  
    int totalSum = 0;         
    int abs_k = abs(k);       

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int distance = abs(i - startRow) + abs(j - startCol);
            
            if (distance <= abs_k) {  
                if (taskType == 1) {
                    if (board[i][j] > 0 && board[i][j] > maxEnergy) {
                        maxEnergy = board[i][j];
                    }
                } else if (taskType == 2) {
                    if (board[i][j] > 0) {
                        totalSum += board[i][j];
                    }
                }
            }
        }
    }

    if (taskType == 1) {
        *result = maxEnergy;
    } else if (taskType == 2) {
        *result = totalSum;
    }

    return 1;  
}
