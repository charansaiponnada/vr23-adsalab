#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int u, v;
} Edge;

int time = 0;
int disc[MAX_VERTICES], low[MAX_VERTICES], parent[MAX_VERTICES];
int visited[MAX_VERTICES];
Edge stack[MAX_VERTICES];
int top = -1;
int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES] = {0}; // Adjacency matrix

void push(Edge e) {
    stack[++top] = e;
}

Edge pop() {
    return stack[top--];
}

void printBCC(int u, int v) {
    printf("BCC: ");
    while (top != -1) {
        Edge e = pop();
        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            printf("(%d, %d) ", e.u, e.v);
            break;
        } else {
            printf("(%d, %d) ", e.u, e.v);
        }
    }
    printf("\n");
}

void BCCUtil(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++time;
	int v;
    for (v = 0; v < MAX_VERTICES; v++) {
        if (adjacencyMatrix[u][v] == 0) continue; // No edge

        if (!visited[v]) {
            parent[v] = u;
            push((Edge){u, v});

            BCCUtil(v);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // If the lowest vertex reachable from subtree under v is below u in DFS tree
            if (low[v] >= disc[u]) {
                printBCC(u, v);
            }
        } else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            push((Edge){u, v});
        }
    }
}

void findBCCs(int n) {
	int i;
    for (i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
	//int i;
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            BCCUtil(i);
            // Print remaining edges in the stack, if any
            if (top != -1) {
                printf("BCC: ");
                while (top != -1) {
                    Edge e = pop();
                    printf("(%d, %d) ", e.u, e.v);
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int n, edges, u, v,i;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (u v):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < n && v >= 0 && v < n) { // Validate vertex indices
            adjacencyMatrix[u][v] = 1;
            adjacencyMatrix[v][u] = 1; // Undirected graph
        } else {
            printf("Invalid edge (%d, %d). Vertex indices must be between 0 and %d.\n", u, v, n-1);
            i--; // Decrement i to retry this edge
        }
    }

    findBCCs(n);

    return 0;
}
