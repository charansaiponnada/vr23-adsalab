#include<stdio.h>
#include<stdlib.h>

int a[20][20], visited[20], n, i, j, v, top=0, size=20;
int stack[20], front=0, rear=0, queue[20];

struct Node {
    int vertex;
    struct Node* next;
};
struct Node* adjList[20];

// Stack operations
void push(int item) {
    if(top != size-1) {
        top++;
        stack[top] = item;
    }
}

int pop() {
    if(top == 0) return 0;
    else return stack[top--];
}

// Queue operations
void enqueue(int item) {
    if(rear != size) {
        if(front == 0 && rear == 0) front = 1;
        rear++;
        queue[rear] = item;
    }
}

int dequeue() {
    if(front == 0 && rear == 0) return 0;
    else if(front == rear) {
        int item = queue[front];
        front = 0; rear = 0;
        return item;
    } else {
        return queue[front++];
    }
}

// DFS for adjacency matrix
void dfsMatrix() {
    if(top != 0) {
        v = pop();
        if(visited[v] == 0) {
            visited[v] = 1;
            printf("%d\n", v);
            for(i = 1; i <= n; i++) {
                if(a[v][i] == 1 && visited[i] == 0) {
                    push(i);
                }
            }
        }
        dfsMatrix();
    }
}

// BFS for adjacency matrix
void bfsMatrix() {
    while(front != 0 && rear != 0) {
        v = dequeue();
        if(visited[v] == 0) {
            visited[v] = 1;
            printf("%d\n", v);
            for(i = 1; i <= n; i++) {
                if(a[v][i] == 1 && visited[i] == 0) {
                    enqueue(i);
                }
            }
        }
    }
}

// DFS for adjacency list
void dfsList() {
    if(top != 0) {
        v = pop();
        if(visited[v] == 0) {
            visited[v] = 1;
            printf("%d\n", v);
            struct Node* temp = adjList[v];
            while(temp != NULL) {
                if(visited[temp->vertex] == 0) {
                    push(temp->vertex);
                }
                temp = temp->next;
            }
        }
        dfsList();  // Recursive DFS
    }
}

// BFS for adjacency list
void bfsList() {
    while(front != 0 && rear != 0) {
        v = dequeue();
        if(visited[v] == 0) {
            visited[v] = 1;
            printf("%d\n", v);
            struct Node* temp = adjList[v];
            while(temp != NULL) {
                if(visited[temp->vertex] == 0) {
                    enqueue(temp->vertex);
                }
                temp = temp->next;
            }
        }
    }
}

// Main function
void main() {
    int st, choice, rep;

    while(1) {
        printf("Enter number of vertices: ");
        scanf("%d", &n);

        printf("Choose 1 for Adjacency Matrix or 2 for Adjacency List: ");
        scanf("%d", &rep);

        if(rep == 1) {
            printf("Enter Adjacency Matrix\n");
            for(i = 1; i <= n; i++) {
                for(j = 1; j <= n; j++) {
                    scanf("%d", &a[i][j]);
                }
            }
        } else if(rep == 2) {
            struct Node *newNode;
            for(i = 1; i <= n; i++) adjList[i] = NULL;
            for(i = 1; i <= n; i++) {
                int v;
                printf("Enter vertices adjacent to vertex %d (-1 to stop): ", i);
                while(1) {
                    scanf("%d", &v);
                    if(v == -1) break;
                    newNode = (struct Node*)malloc(sizeof(struct Node));
                    newNode->vertex = v;
                    newNode->next = adjList[i];
                    adjList[i] = newNode;
                }
            }
        }

        printf("Enter the starting vertex: ");
        scanf("%d", &st);

        while(1) {
            printf("Choose 1 for DFS or 2 for BFS: ");
            scanf("%d", &choice);

            // Reset visited array
            for(i = 1; i <= n; i++) visited[i] = 0;

            if(rep == 1 && choice == 1) {
                // DFS for adjacency matrix
                push(st);
                printf("DFS (Adjacency Matrix):\n");
                dfsMatrix();
            } else if(rep == 1 && choice == 2) {
                // BFS for adjacency matrix
                enqueue(st);
                printf("BFS (Adjacency Matrix):\n");
                bfsMatrix();
            } else if(rep == 2 && choice == 1) {
                // DFS for adjacency list
                push(st);
                printf("DFS (Adjacency List):\n");
                dfsList();
            } else if(rep == 2 && choice == 2) {
                // BFS for adjacency list
                enqueue(st);
                printf("BFS (Adjacency List):\n");
                bfsList();
            }

            printf("Do you want to continue with DFS/BFS? (1 for Yes / 0 for No): ");
            int cont;
            scanf("%d", &cont);
            if(cont == 0) break;
        }

        printf("Do you want to continue with a new graph? (1 for Yes / 0 for No): ");
        int cont;
        scanf("%d", &cont);
        if(cont == 0) break;
    }
}
