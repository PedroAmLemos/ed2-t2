#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct AdjList{
    Vertex_t start;
    List_t edges;
}AdjList;

Graph_t create_graph(){
    return create_list();
}

Vertex_t get_graph_vertex(AdjList_t _adj_list){
    AdjList *adj_list = (AdjList*)_adj_list;
    return adj_list->start;
}

List_t get_graph_edges(AdjList_t _adj){
    AdjList *al = (AdjList*)_adj;
    return al->edges;
}

AdjList_t get_graph_adj_list(Graph_t _graph, char* vertex_name){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        AdjList* al = get_list_info(node);
        if(strcmp(vertex_name, get_vertex_name(al->start)) == 0){
            return al;
        }
    }
    return NULL;
}

ListNode_t get_graph_node(Graph_t _graph, char* vertex_name){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        AdjList* al = get_list_info(node);
        if(strcmp(vertex_name, get_vertex_name(al->start)) == 0){
            return node;
        }
    }
    return NULL;
}

void add_graph_vertex(Graph_t _graph, Vertex_t _vertex){
    AdjList *adj = (AdjList *) malloc(sizeof(AdjList));
    adj->start = _vertex;
    adj->edges = create_list();
    insert_list(_graph, adj);
}

void add_graph_edge(Graph_t _graph, Edge_t _edge){
    AdjList *al = get_graph_adj_list(_graph, get_edge_begin_vertex_name(_edge));
    if(al == NULL){
        return;
    }
    insert_list(al->edges, _edge);
}

void delete_adj_list(AdjList_t _adj){
    AdjList *al = (AdjList*) _adj;
    // TODO see this
    remove_list(al->edges, free);
    free(get_vertex_point(al->start));
    free(al->start);
    free(_adj);
}

void delete_graph(Graph_t _graph){
    remove_list(_graph, NULL);
}

void delete_full_graph(Graph_t _graph){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        delete_adj_list(get_list_info(node));
    }
    delete_graph(_graph);
}








