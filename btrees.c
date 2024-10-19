#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define MIN (MAX / 2)

typedef struct BTreeNode {
    int keys[MAX + 1];
    int count;
    struct BTreeNode* children[MAX + 1];
} BTreeNode;

BTreeNode* root = NULL;

BTreeNode* createNode(int key, BTreeNode* child) {
	int i;
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->keys[1] = key;
    newNode->count = 1;
    newNode->children[0] = root;
    newNode->children[1] = child;
    for (i = 2; i <= MAX; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insertValue(int key, int pos, BTreeNode* node, BTreeNode* child) {
    int j = node->count;
    while (j > pos) {
        node->keys[j + 1] = node->keys[j];
        node->children[j + 1] = node->children[j];
        j--;
    }
    node->keys[j + 1] = key;
    node->children[j + 1] = child;
    node->count++;
}

void splitNode(int key, int* pval, int pos, BTreeNode* node, BTreeNode* child, BTreeNode** newNode) {
    int median = (pos > MIN) ? MIN + 1 : MIN;
    *newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    int j = median + 1;
    while (j <= MAX) {
        (*newNode)->keys[j - median] = node->keys[j];
        (*newNode)->children[j - median] = node->children[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        insertValue(key, pos, node, child);
    } else {
        insertValue(key, pos - median, *newNode, child);
    }

    *pval = node->keys[node->count];
    (*newNode)->children[0] = node->children[node->count];
    node->count--;
}

int setValue(int key, int* pval, BTreeNode* node, BTreeNode** child) {
    int pos;
    if (!node) {
        *pval = key;
        *child = NULL;
        return 1;
    }

    if (key < node->keys[1]) {
        pos = 0;
    } else {
        for (pos = node->count; (key < node->keys[pos] && pos > 1); pos--);
        if (key == node->keys[pos]) {
            printf("Duplicate keys are not allowed\n");
            return 0;
        }
    }
 
    if (setValue(key, pval, node->children[pos], child)) {
        if (node->count < MAX) {
            insertValue(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

void insert(int key) {
    int flag, i;
    BTreeNode* child;

    flag = setValue(key, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

void deleteNode(int key, BTreeNode* node) {
    int pos, flag = 0,i;
    if (!node) {
        printf("Tree is empty\n");
        return;
    }

    if (key < node->keys[1]) {
        pos = 0;
    } else {
        for (pos = node->count; (key < node->keys[pos] && pos > 1); pos--);
        if (key == node->keys[pos])
            flag = 1;
    }

    if (flag) {
        for ( i = pos; i < node->count; i++) {
            node->keys[i] = node->keys[i + 1];
            node->children[i] = node->children[i + 1];
        }
        node->count--;
        printf("Deleted key: %d\n", key);
    } else {
        deleteNode(key, node->children[pos]);
    }
}

void printInOrder(BTreeNode* node) {
    if (node) {
        int i;
        for (i = 0; i < node->count; i++) {
            printInOrder(node->children[i]);
            printf("%d ", node->keys[i + 1]);
        }
        printInOrder(node->children[i]);
    }
}

void traverse(BTreeNode* node, int level) {
    if (node) {
        int i;
        for (i = 0; i < level; i++) printf("  ");
        printf("Level %d: ", level);
        for (i = 1; i <= node->count; i++) {
            printf("%d ", node->keys[i]);
        }
        printf("\n");
        for (i = 0; i <= node->count; i++) {
            traverse(node->children[i], level + 1);
        }
    }
}

int main() {
    int i, n, key;
    printf("Enter the number of elements (<=100): ");
    scanf("%d", &n);

    if (n > 100) {
        printf("Exceeded max limit of 100 elements!\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(key);
    }

    printf("B-Tree structure:\n");
    traverse(root, 0);
    printf("\n");

    printf("B-Tree in-order traversal:\n");
    printInOrder(root);
    printf("\n");

    printf("Enter the key to delete: ");
    scanf("%d", &key);
    deleteNode(key, root);

    printf("B-Tree structure after deletion:\n");
    traverse(root, 0);
    printf("\n");

    printf("B-Tree in-order traversal after deletion:\n");
    printInOrder(root);
    printf("\n");

    return 0;
}
