#include <stdio.h>
int i,w;
int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int W, int wt[], int val[], int n) {
    int dp[W + 1];

    for ( i = 0; i <= W; i++) {
        dp[i] = 0;
    }

    for (i = 0; i < n; i++) {
        for (w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }

    return dp[W];
}

int main() {
    int n, W;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int wt[n], val[n];

    printf("Enter the maximum capacity of the knapsack: ");
    scanf("%d", &W);

    printf("Enter the weights and values of the items:\n");
    for (i = 0; i < n; i++) {
        printf("Item %d: Weight: ", i + 1);
        scanf("%d", &wt[i]);
        printf("Item %d: Value: ", i + 1);
        scanf("%d", &val[i]);
    }

    int result = knapSack(W, wt, val, n);
    printf("Maximum profit: %d\n", result);

    return 0;
}
//output:
//Enter the number of items: 3
//Enter the maximum capacity of the knapsack: 50
//Enter the weights and values of the items:
//Item 1: Weight: 10
//Item 1: Value: 60
//Item 2: Weight: 20
//Item 2: Value: 100
//Item 3: Weight: 30
//Item 3: Value: 120
//Maximum profit: 220
//
//--------------------------------
//Process exited after 23.94 seconds with return value 0
//Press any key to continue . . .
