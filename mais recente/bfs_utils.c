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

typedef struct QueueNodeList {
    QueueNode node;
    struct QueueNodeList *next;
} QueueNodeList;

typedef struct {
    QueueNodeList *front;
    QueueNodeList *back;
    int size;
} Queue;

Queue* createQueue() {
    Queue *queue = (Queue *)calloc(1, sizeof(Queue));
    return queue;
}

void freeQueue(Queue *queue) {
    if (queue) {
        QueueNodeList *current = queue->front;
        while (current) {
            QueueNodeList *next = current->next;
            free(current);
            current = next;
        }
        free(queue);
    }
}

bool isQueueEmpty(Queue *queue) {
    return queue->size == 0;
}

void enqueue(Queue *queue, int row, int col, int distance) {
    QueueNodeList *newNode = (QueueNodeList *)malloc(sizeof(QueueNodeList));
    newNode->node.row = row;
    newNode->node.col = col;
    newNode->node.distance = distance;
    newNode->next = NULL;
    if (queue->back) {
        queue->back->next = newNode;
    } else {
        queue->front = newNode;
    }
    queue->back = newNode;
    queue->size++;
}

QueueNode dequeue(Queue *queue) {
    QueueNode node = {0, 0, 0};
    if (queue->front) {
        QueueNodeList *frontNode = queue->front;
        node = frontNode->node;
        queue->front = frontNode->next;
        if (!queue->front) {
            queue->back = NULL;
        }
        free(frontNode);
        queue->size--;
    }
    return node;
}

int bfs(int **board, int rows, int cols, int startRow, int startCol, int k, int taskType, int *result) {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    Queue *queue = createQueue();
    if (!queue) {
        return 0;
    }

    bool *visited = (bool *)calloc(rows * cols, sizeof(bool));
    if (!visited) {
        freeQueue(queue);
        return 0;
    }

    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        free(visited);
        freeQueue(queue);
        return 0;
    }

    enqueue(queue, startRow, startCol, 0);
    visited[startRow * cols + startCol] = true;

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

                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow * cols + newCol]) {
                        enqueue(queue, newRow, newCol, currentDistance + 1);
                        visited[newRow * cols + newCol] = true;
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

                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow * cols + newCol]) {
                        enqueue(queue, newRow, newCol, currentDistance + 1);
                        visited[newRow * cols + newCol] = true;
                    }
                }
            }
        }
        *result = totalSum;
    } 

    free(visited);
    freeQueue(queue);

    return 1;
}