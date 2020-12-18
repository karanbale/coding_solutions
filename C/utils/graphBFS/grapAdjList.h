#include "../../standardHeaders.h"

// structure for each vertex of the graph
typedef struct vertex{
    int value;
    struct  vertex *next;
} vertex_t;

// structure to hold pointer to the adj list of these vertices
typedef struct graph{
    int numOfVertices;
    vertex_t **adjListHead;
}graph_t;

typedef struct queue{
    int front;
    int end;
    int numOfVertices;
    int *notVisited;
    int *visited;
}queue_t;

vertex_t *createNewVertex(int value);
graph_t *createGraph(int numVertices);
void addVertex(graph_t *graph, int srcVertex, int dstVertex, bool isUnidirectional);
void removeVertex(graph_t *graph, int vertexValue);
void printGraph(graph_t *graph);
