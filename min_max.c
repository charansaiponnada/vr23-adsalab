//code for week-6 and program 1
#include <stdio.h>

struct Pair {
    int min;
    int max;
};

struct Pair findMinMax(int arr[], int low, int high) {
    struct Pair result, left, right;
    
    if (low == high) {
        result.min = result.max = arr[low];
        return result;
    }
    
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            result.max = arr[low];
            result.min = arr[high];
        } else {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }
    
    int mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);
    
    result.min = (left.min < right.min) ? left.min : right.min;
    result.max = (left.max > right.max) ? left.max : right.max;
    
    return result;
}

int main() {
    int n, i;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    struct Pair result = findMinMax(arr, 0, n - 1);
    printf("Minimum: %d\n", result.min);
    printf("Maximum: %d\n", result.max);
    
    return 0;
}
