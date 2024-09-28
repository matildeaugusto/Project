#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "bfs_utils.h"
#include "board_utils.h"

typedef struct {
    int row;
    int col;
    int distance;
} QueueNode;

typedef struct {
    QueueNode *nodes;
    int front;
    int back;
    int capacity;
    int size;
} Queue;

Queue* createQueue(int capacity) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->nodes = (QueueNode *)malloc(capacity * sizeof(QueueNode));
    if (!queue->nodes) {
        free(queue);
        return NULL;
    }
    queue->front = 0;
    queue->back = 0;
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

void freeQueue(Queue *queue) {
    if (queue) {
        free(queue->nodes);
        free(queue);
    }
}

bool isQueueEmpty(Queue *queue) {
    return queue->size == 0;
}

void enqueue(Queue *queue, int row, int col, int distance) {
    queue->nodes[queue->back].row = row;
    queue->nodes[queue->back].col = col;
    queue->nodes[queue->back].distance = distance;
    queue->back = (queue->back + 1) % queue->capacity;
    queue->size++;
}

QueueNode dequeue(Queue *queue) {
    QueueNode node = queue->nodes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return node;
}

int bfs(int **board, int rows, int cols, int startRow, int startCol, int k, int taskType, int *result) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    Queue *queue = createQueue(rows * cols);
    if (!queue) {
        return 0;
    }

    bool **visited = (bool **)malloc(rows * sizeof(bool *));
    if (!visited) {
        freeQueue(queue);
        return 0;
    }
    for (int i = 0; i < rows; i++) {
        visited[i] = (bool *)calloc(cols, sizeof(bool));
        if (!visited[i]) {
            for (int j = 0; j < i; j++) {
                free(visited[j]);
            }
            free(visited);
            freeQueue(queue);
            return 0;
        }
    }

    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
        }
        free(visited);
        freeQueue(queue);
        return 0;
    }

    enqueue(queue, startRow, startCol, 0);
    visited[startRow][startCol] = true;

    if (taskType == 1) {
        int maxEnergy = INT_MIN;
        while (!isQueueEmpty(queue)) {
            QueueNode current = dequeue(queue);
            int currentRow = current.row;
            int currentCol = current.col;
            int currentDistance = current.distance;

            if (!(currentRow == startRow && currentCol == startCol)) {
                if (board[currentRow][currentCol] > 0) {
                    if (board[currentRow][currentCol] > maxEnergy) {
                        maxEnergy = board[currentRow][currentCol];
                    }
                }
            }

            if (currentDistance < abs(k)) {
                for (int d = 0; d < 4; d++) {
                    int newRow = currentRow + directions[d][0];
                    int newCol = currentCol + directions[d][1];

                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]) {
                        enqueue(queue, newRow, newCol, currentDistance + 1);
                        visited[newRow][newCol] = true;
                    }
                }
            }
        }
        *result = maxEnergy;
    } else if (taskType == 2) {
        int totalSum = 0;
        while (!isQueueEmpty(queue)) {
            QueueNode current = dequeue(queue);
            int currentRow = current.row;
            int currentCol = current.col;
            int currentDistance = current.distance;

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
                        enqueue(queue, newRow, newCol, currentDistance + 1);
                        visited[newRow][newCol] = true;
                    }
                }
            }
        }
        *result = totalSum;
    } else if (taskType == 3) {
        int endRow = result[0];
        int endCol = result[1];
        while (startRow != endRow) {
            if (startRow > endRow) {
                startRow--;
            } else {
                startRow++;
            }  
        }

        while (startCol != endCol) {
            if (startCol > endCol) {
                startCol--;
            } else {
                startCol++;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    freeQueue(queue);

    return 1;
}
