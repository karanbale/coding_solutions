
#include "grapAdjList.h"

vertex_t *createNewVertex(int value){
    vertex_t *newVertex = malloc(sizeof(vertex_t));
    newVertex->value = value;
    newVertex->next = NULL;
    return newVertex;
}

graph_t *createGraph(int numVertices){
    graph_t *graph = malloc(sizeof(graph_t));
    graph->numOfVertices = numVertices;

    graph->adjListHead = malloc(sizeof(vertex_t *)*numVertices);
    for(int i=0; i<numVertices; i++){
        graph->adjListHead[i] = NULL;
    }

    return graph;
}

void addVertex(graph_t *graph, int srcVertex, int dstVertex, bool isUnidirectional){

    vertex_t *newVertex = createNewVertex(dstVertex);
    
    // append source vertex to destination vertext
    if(graph->adjListHead[srcVertex] == NULL){
        graph->adjListHead[srcVertex] = newVertex;
    }
    else{
        newVertex->next = graph->adjListHead[srcVertex]->next;
        graph->adjListHead[srcVertex] = newVertex;
    }

    // if the graph is not unidirectional, add link between destination and souce as well
    if(!isUnidirectional){
        vertex_t *newVertex = createNewVertex(srcVertex);

        if(graph->adjListHead[dstVertex] == NULL){
            graph->adjListHead[dstVertex] = newVertex;
        }
        else{
            newVertex->next = graph->adjListHead[dstVertex]->next;
            graph->adjListHead[dstVertex] = newVertex;
        }
    }
}


void removeVertex(graph_t *graph, int vertexValue){

}

void printGraph(graph_t *graph){
    for(int i = 0; i< graph->numOfVertices; i++){
        vertex_t *temp = graph->adjListHead[i];
        while(temp){
            printf("%d->\n", temp->value);
            temp = temp->next;
        }
    }
}

// Driver program to test above functions 
int main() 
{ 
    // create the graph given in above fugure 
    int V = 5; 
    graph_t* graph = createGraph(V); 
    addVertex(graph, 0, 1, 0); 
    addVertex(graph, 0, 4, 0);
    addVertex(graph, 1, 2, 0); 
    addVertex(graph, 1, 3, 0); 
    addVertex(graph, 1, 4, 0); 
    addVertex(graph, 2, 3, 0); 
    addVertex(graph, 3, 4, 0); 
  
    // print the adjacency list representation of the above graph 
    printGraph(graph); 
  
    return 0; 
} 