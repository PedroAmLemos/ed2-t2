#include <stdlib.h>
#include "graph.h"
#include "linked_list.h"
#include "vertex.h"

typedef struct AdjList{
    Vertex_t start;
    List_t edges;
}AdjList;

Graph_t create_graph(){
    return create_list();
}


void add_graph_vertex(Graph_t _graph, Vertex_t _vertex){
    AdjList *adj = (AdjList *) malloc(sizeof(AdjList));
    adj->start = _vertex;
    adj->edges = create_list();
    insert_list(_graph, adj);
}


// void adicionaVertice(Graph graph, Vertice vertice){
//     AdjascentListStruct* als = (AdjascentListStruct*)malloc(sizeof(AdjascentListStruct));
//     als->inicio = vertice;
//     als->arestas = create();
//     insert(graph, als);
// }
