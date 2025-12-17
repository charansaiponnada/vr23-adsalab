#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} Heap;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(Heap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

void maxHeapify(Heap *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

void insertMinHeap(Heap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full\n");
        return;
    }
    heap->data[heap->size++] = value;

    int index = heap->size - 1;
    while (index != 0 && heap->data[(index - 1) / 2] > heap->data[index]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void insertMaxHeap(Heap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full\n");
        return;
    }
    heap->data[heap->size++] = value;

    int index = heap->size - 1;
    while (index != 0 && heap->data[(index - 1) / 2] < heap->data[index]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void deleteMinHeap(Heap *heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return;
    }
    heap->data[0] = heap->data[--heap->size];
    minHeapify(heap, 0);
}

void deleteMaxHeap(Heap *heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return;
    }
    heap->data[0] = heap->data[--heap->size];
    maxHeapify(heap, 0);
}

void printHeapTree(Heap *heap, int index, int level) {
    if (index >= heap->size) {
        return;
    }
    printHeapTree(heap, 2 * index + 2, level + 1);
    printf("%*s%d\n", 4 * level, "", heap->data[index]);
    printHeapTree(heap, 2 * index + 1, level + 1);
}

void displayHeap(Heap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return;
    }
    printHeapTree(heap, 0, 0);
}

int main() {
    Heap minHeap = { .size = 0 };
    Heap maxHeap = { .size = 0 };
    int choice, n, i, values[MAX_SIZE];

    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    while (1) {
        printf("1. Insert into Min Heap\n");
        printf("2. Insert into Max Heap\n");
        printf("3. Delete from Min Heap\n");
        printf("4. Delete from Max Heap\n");
        printf("5. Display Min Heap\n");
        printf("6. Display Max Heap\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for( i = 0; i < n; i++) {
                    insertMinHeap(&minHeap, values[i]);
                }
                printf("Inserted elements into Min Heap\n");
                break;
            case 2:
                for (i = 0; i < n; i++) {
                    insertMaxHeap(&maxHeap, values[i]);
                }
                printf("Inserted elements into Max Heap\n");
                break;
            case 3:
                deleteMinHeap(&minHeap);
                break;
            case 4:
                deleteMaxHeap(&maxHeap);
                break;
            case 5:
                printf("Min Heap:\n");
                displayHeap(&minHeap);
                break;
            case 6:
                printf("Max Heap:\n");
                displayHeap(&maxHeap);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
