#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int i, j;

bool *cols, *diag1, *diag2;

bool isSafe(int row, int col, int N) {
    return !cols[col] && !diag1[row - col + N - 1] && !diag2[row + col];
}

void mark(int row, int col, bool state, int N) {
    cols[col] = state;
    diag1[row - col + N - 1] = state;
    diag2[row + col] = state;
}

bool solveNQUtil(int **board, int row, int N) {
    if (row >= N) return true;
    int col;
    for (col = 0; col < N; col++) {
        if (isSafe(row, col, N)) {
            board[row][col] = 1;
            mark(row, col, true, N);

            if (solveNQUtil(board, row + 1, N)) {
                return true;
            }

            board[row][col] = 0;
            mark(row, col, false, N);
        }
    }
    return false;
}

void printSolution(int **board, int N) {
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j]) printf("Q ");
            else printf(". ");
        }
        printf("\n");
    }
}

bool solveNQ(int size) {
    int N = size;
    int **board;

    board = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        board[i] = (int *)malloc(N * sizeof(int));
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    cols = (bool *)malloc(N * sizeof(bool));
    diag1 = (bool *)malloc((2 * N - 1) * sizeof(bool));
    diag2 = (bool *)malloc((2 * N - 1) * sizeof(bool));

    if (cols == NULL || diag1 == NULL || diag2 == NULL || board == NULL) {
        printf("Memory allocation failed\n");
        return false;
    }

    for (i = 0; i < N; i++) {
        cols[i] = diag1[i] = diag2[i] = false;
    }
    for (i = N; i < 2 * N - 1; i++) {
        diag1[i] = diag2[i] = false;
    }

    if (!solveNQUtil(board, 0, N)) {
        printf("Solution does not exist\n");

        for (i = 0; i < N; i++) {
            free(board[i]);
        }
        free(board);
        free(cols);
        free(diag1);
        free(diag2);

        return false;
    }

    printSolution(board, N);

    for (i = 0; i < N; i++) {
        free(board[i]);
    }
    free(board);
    free(cols);
    free(diag1);
    free(diag2);

    return true;
}

int main() {
    int size;
    printf("Enter the size of the board (N): ");
    scanf("%d", &size);

    if (size <= 3) {
        printf("No solution exists for N <= 3\n");
    } else {
        solveNQ(size);
    }
    return 0;
}
//output:
//Enter the size of the board (N): 8
//Q . . . . . . .
//. . . . Q . . .
//. . . . . . . Q
//. . . . . Q . .
//. . Q . . . . .
//. . . . . . Q .
//. Q . . . . . .
//. . . Q . . . .
//
//--------------------------------
//Process exited after 2.334 seconds with return value 0
//Press any key to continue . . .
