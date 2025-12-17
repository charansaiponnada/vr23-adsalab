#include <stdio.h>
#include <stdlib.h>
int i ,j;
typedef struct Job {
    char id;
    int dead;
    int profit;
} Job;

int compare(const void* a, const void* b) {
    Job* job1 = (Job*)a;
    Job* job2 = (Job*)b;
    return job2->profit - job1->profit;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void printJobScheduling(Job arr[], int n) {
    qsort(arr, n, sizeof(Job), compare);

    int result[n];
    int slot[n];

    for ( i = 0; i < n; i++) {
        slot[i] = 0;
    }

    for (i = 0; i < n; i++) {
        for (j = min(n, arr[i].dead) - 1; j >= 0; j--) {
            if (slot[j] == 0) {
                result[j] = i;
                slot[j] = 1;
                break;
            }
        }
    }

    printf("Job Sequence for maximum profit: ");
    for (i = 0; i < n; i++) {
        if (slot[i]) {
            printf("%c ", arr[result[i]].id);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter job %d details (ID, Deadline, Profit): ", i + 1);
        scanf(" %c %d %d", &arr[i].id, &arr[i].dead, &arr[i].profit);
    }

    printJobScheduling(arr, n);
    return 0;
}
//output:
//Enter the number of jobs: 4
//Enter job 1 details (ID, Deadline, Profit): a 4 20
//Enter job 2 details (ID, Deadline, Profit): b 1 10
//Enter job 3 details (ID, Deadline, Profit): c 1 40
//Enter job 4 details (ID, Deadline, Profit): d 1 30
//Job Sequence for maximum profit: c a
//
//--------------------------------
//Process exited after 31.19 seconds with return value 0
//Press any key to continue . . .
