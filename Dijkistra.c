#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MAX 100

int adjMatrix[MAX][MAX];

struct Node {
    int vertex, weight;
    struct Node* next;
};
struct Node* adjList[MAX];

struct Node* createNode(int v, int weight) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdgeAdjList(int u, int v, int weight) {
    struct Node* newNode = createNode(v, weight);
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void dijkstraMatrix(int n, int src) {
    int dist[MAX], visited[MAX] = {0},i,count,v;

    for ( i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    for ( count = 0; count < n - 1; count++) {
        int min = INF, u;

        for ( v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v], u = v;
            }
        }

        visited[u] = 1;

        for ( v = 0; v < n; v++) {
            if (!visited[v] && adjMatrix[u][v] && dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    printf("Dijkstra (Adjacency Matrix): \n");
    for ( i = 0; i < n; i++) {
        printf("Vertex %d -> Distance: %d\n", i, dist[i]);
    }
}

void dijkstraList(int n, int src) {
    int dist[MAX], visited[MAX] = {0},i,count,v;

    for ( i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    for ( count = 0; count < n - 1; count++) {
        int min = INF, u;

        for ( v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v], u = v;
            }
        }

        visited[u] = 1;

        struct Node* temp = adjList[u];
        while (temp) {
            int v = temp->vertex;
            if (!visited[v] && dist[u] != INF && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("Dijkstra (Adjacency List): \n");
    for ( i = 0; i < n; i++) {
        printf("Vertex %d -> Distance: %d\n", i, dist[i]);
    }
}

int main() {
    int n, u, v, weight, edges,i,j;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    for ( i = 0; i < edges; i++) {
        printf("Enter edge (u v weight): ");
        scanf("%d %d %d", &u, &v, &weight);
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
        addEdgeAdjList(u, v, weight);
        addEdgeAdjList(v, u, weight);
    }

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstraMatrix(n, src);
    dijkstraList(n, src);

    return 0;
}
// output:
// Enter the number of vertices: 5
// Enter the number of edges: 6
// Enter edge (u v weight): 0 1 10
// Enter edge (u v weight): 0 4 5
// Enter edge (u v weight): 1 2 1
// Enter edge (u v weight): 2 3 4
// Enter edge (u v weight): 3 4 3
// Enter edge (u v weight): 0 2 6
// Enter the source vertex: 0
// Dijkstra (Adjacency Matrix):
// Vertex 0 -> Distance: 0
// Vertex 1 -> Distance: 7
// Vertex 2 -> Distance: 6
// Vertex 3 -> Distance: 8
// Vertex 4 -> Distance: 5
// Dijkstra (Adjacency List):
// Vertex 0 -> Distance: 0
// Vertex 1 -> Distance: 7
// Vertex 2 -> Distance: 6
// Vertex 3 -> Distance: 8
// Vertex 4 -> Distance: 5

// --------------------------------
// Process exited after 41.21 seconds with return value 0
// Press any key to continue . . .
