#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "svg.h"
#include "edge.h"
#include "union_find.h"
#include "graph.h"
#include "reading_utility.h"
#include "vertex.h"

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

AdjList_t get_graph_adj_list_vertex(Graph_t _graph, char* vertex_name){
    AdjList *al;
    al = (AdjList*) get_graph_adj_list(_graph, vertex_name);
    return al->start;
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

Graph_t create_graph_copy(Graph_t graph){
    Graph_t copy = create_graph();
    AdjList *adj = NULL;
    ListNode_t edge_list = NULL;
    Vertex_t vertex = NULL;
    for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
        adj = (AdjList *) get_list_info(node);
        edge_list = adj->edges;
        vertex = adj->start;
        add_graph_vertex_copy(copy, vertex);
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            add_graph_edge_copy(copy, get_list_info(edge_node));
        }
    }
    return copy;
}

void clean_adj_edges(AdjList_t _adj){
    AdjList *adj = (AdjList *) _adj;
    remove_list(adj->edges, free);
    adj->edges = create_list();
}

void add_graph_edge_copy(Graph_t _graph, Edge_t _edge){
    AdjList *al = get_graph_adj_list(_graph, get_edge_begin_vertex_name(_edge));
    if(al == NULL){
        return;
    }
    Edge_t edge = NULL;
    edge = create_edge(get_edge_name(_edge), get_edge_begin_vertex_name(_edge), get_edge_end_vertex_name(_edge), get_edge_ldir(_edge), get_edge_lesq(_edge), get_edge_cmp(_edge), get_edge_vm(_edge));
    insert_list(al->edges, edge);
}

void add_graph_vertex_copy(Graph_t _graph, Vertex_t _vertex){
    AdjList *adj = (AdjList *) malloc(sizeof(AdjList));
    Vertex_t copy = create_vertex(get_vertex_name(_vertex), get_vertex_x(_vertex), get_vertex_y(_vertex));
    adj->start = copy;
    adj->edges = create_list();
    insert_list(_graph, adj);
}

int on_adj_list(AdjList_t _adj, char *begin, char *end){
    AdjList *adj = (AdjList *) _adj;
    List_t edge_list = adj->edges;
    Edge_t edge = NULL;
    char *begin_vertex = NULL;
    char *ending_vertex = NULL;
    for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
        edge = get_list_info(edge_node);
        begin_vertex = get_edge_begin_vertex_name(edge);
        ending_vertex = get_edge_end_vertex_name(edge);
        if(strcmp(begin_vertex, begin) == 0 && strcmp(ending_vertex, end) == 0){
            return 1;
        }
    }
    return 0;
}

Graph_t agm_kruskal(Graph_t _graph){

    List_t edges = create_list();
    List_t edge_list = NULL;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        edge_list = get_graph_edges(get_list_info(node));
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            insert_list(edges, get_list_info(edge_node));
        }
    }

    quick_sort_edge_list(edges, 0, get_list_size(edges)-1);

    UnionFind_t union_find = create_union_find(_graph);
    for(ListNode_t node = get_list_first(edges); node != NULL; node = get_list_next(node)){
        union_union_find(union_find, get_list_info(node));
    }

    Graph_t agm = NULL;
    agm = create_graph_copy(get_list_info(get_list_first(union_find)));

    remove_list(union_find, union_find_remove_aux);
    remove_list(edges, NULL);

    return agm;
}

void union_find_remove_aux(Graph_t _graph){
    AdjList_t adj_list = NULL;
    List_t edge_list = NULL;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        edge_list = get_graph_edges(adj_list);
        remove_list(edge_list, NULL);
        free(adj_list);
    }
    remove_list(_graph, NULL);
}
