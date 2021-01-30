#include "grapAdjList.h"

vertex_t *createNewVertex(int value){
    vertex_t *newVertex = malloc(sizeof(vertex_t));
    newVertex->value = value;
    newVertex->visited = false;
    newVertex->next = NULL;
    return newVertex;
}

graph_t *createGraph(int numVertices){
    graph_t *graph = (graph_t *) malloc(sizeof(graph_t));
    graph->numOfVertices = numVertices;

    graph->graphAdjList =  (graphAdjList_t *) malloc(sizeof(graphAdjList_t) * numVertices);
    for(int i=0; i<numVertices; i++){
        graph->graphAdjList[i].adjListHead = NULL;
    }
    return graph;
}

void addVertex(graph_t *graph, int srcVertex, int dstVertex, bool isUnidirectional){

    vertex_t *newDstNode = createNewVertex(dstVertex);

    newDstNode->next = graph->graphAdjList[srcVertex].adjListHead;
    graph->graphAdjList[srcVertex].adjListHead = newDstNode;

    // if the graph is not unidirectional, add link between destination and souce as well
    if(!isUnidirectional){
        vertex_t *newSrcNode = createNewVertex(srcVertex);
        newSrcNode->next = graph->graphAdjList[dstVertex].adjListHead;
        graph->graphAdjList[dstVertex].adjListHead = newSrcNode;
    }
}

void freeGraph(graph_t *graph){
    for(int i = 0; i< graph->numOfVertices; i++){
        vertex_t *temp = graph->graphAdjList[i].adjListHead;
        while(temp){
            graph->graphAdjList[i].adjListHead = graph->graphAdjList[i].adjListHead->next;
            free(temp);
            temp = graph->graphAdjList[i].adjListHead;
        }
    }
    free(graph);
}

void printGraph(graph_t *graph){
    for(int i = 0; i< graph->numOfVertices; i++){
        vertex_t *temp = graph->graphAdjList[i].adjListHead;
        printf("\n Adjacency list of vertex %d\n head ", i); 
        while(temp){
            printf("->%d\n", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

bool isSafe(graph_t *graph, int rowIdx, int colIdx, int rowSize, int colSize, int item){
    if((rowIdx >= 0 && rowIdx < rowSize) && (colIdx >= 0 && colIdx < colSize) &&
        !graph->graphAdjList[item].adjListHead->visited){
            return true;
        }
    return false;
}

void bfs(graph_t *graph, queue_t *queue, int firstVertex){
    // mark current vertex as visited
    if(graph->graphAdjList[firstVertex].adjListHead == NULL){
        return;
    }
    else{
        graph->graphAdjList[firstVertex].adjListHead->visited = true;
        insertQueue(queue, firstVertex);
    }
    // check if its end of the traversal, go back
    while(!isQueueEmpty(queue)){
        int nextVertex = removeQueue(queue);
        // get next neighboring vertex of current vertex
        // condition to get neighboring vertex would be,
        vertex_t *nextNode = graph->graphAdjList[nextVertex].adjListHead->next;
        nextNode = nextNode->next;
        insertQueue(queue, nextNode->value);
    }
}

// Driver program to test above functions 
int main() 
{ 
    // create the graph given in above fugure 
    int V = 5; 
    graph_t *graph = createGraph(V);
    queue_t *queue = createQueue(V);

    addVertex(graph, 0, 1, 0); 
    addVertex(graph, 0, 4, 0);
    addVertex(graph, 1, 2, 0); 
    addVertex(graph, 1, 3, 0); 
    addVertex(graph, 1, 4, 0); 
    addVertex(graph, 2, 3, 0); 
    addVertex(graph, 3, 4, 0); 
  
    // print the adjacency list representation of the above graph 
    printGraph(graph); 
    freeGraph(graph);

    return 0; 
} 