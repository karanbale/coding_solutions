#include "../../standardHeaders.h"
#include "../queue/queue.h"

// structure for each vertex of the graph
typedef struct vertex{
    int value;
    bool visited;
    struct  vertex *next;
}vertex_t;

typedef struct graphAdjList
{
    vertex_t *adjListHead;
}graphAdjList_t;

// structure to hold pointer to the adj list of these vertices
typedef struct graph{
    int numOfVertices;
    graphAdjList_t *graphAdjList;
}graph_t;

vertex_t *createNewVertex(int value);
graph_t *createGraph(int numVertices);
void addVertex(graph_t *graph, int srcVertex, int dstVertex, bool isUnidirectional);
void removeVertex(graph_t *graph, int vertexValue);
void printGraph(graph_t *graph);
void bfs(graph_t *graph, queue_t *queue, int firstVertex);
