#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "svg.h"
#include "union_find.h"
#include "linked_list.h"
#include "vertex.h"

UnionFind_t create_union_find(Graph_t _graph){
    List_t union_find = create_list();
    Vertex_t vertex = NULL;
    Graph_t empty_graph = NULL;

    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        vertex = get_graph_vertex(get_list_info(node));
        empty_graph = create_graph();
        add_graph_vertex(empty_graph, vertex);
        insert_list(union_find, empty_graph);
    }

    return union_find;
}

int find_union_find(UnionFind_t _union_find, char *id){
    Vertex_t vertex = NULL;
    Graph_t graph = NULL;
    int result = 0;
    for(ListNode_t node = get_list_first(_union_find); node != NULL; node = get_list_next(node)){
        graph = get_list_info(node);
        for(ListNode_t graph_node = get_list_first(graph); graph_node != NULL; graph_node = get_list_next(graph_node)){
            vertex = get_graph_vertex(get_list_info(graph_node));
            if(strcmp(id, get_vertex_name(vertex)) == 0){
                return result;
            }
        }
        result++;
    }
    return -1;
}

void union_union_find(UnionFind_t _union_find, Edge_t edge){
    char *begin_vertex_name = get_edge_begin_vertex_name(edge);
    char *end_vertex_name = get_edge_end_vertex_name(edge);

    ListNode_t graph_begin_node = NULL;
    ListNode_t graph_end_node = NULL;

    Graph_t graph_begin = NULL;
    Graph_t graph_end = NULL;

    int graph_begin_index = find_union_find(_union_find, begin_vertex_name);
    int graph_end_index = find_union_find(_union_find, end_vertex_name);

    if(graph_begin_index != graph_end_index && graph_begin_index != -1 && graph_end_index != -1){

        graph_begin_node = get_list_index_node(_union_find, graph_begin_index);
        graph_end_node = get_list_index_node(_union_find, graph_end_index);

        graph_begin = get_list_info(graph_begin_node);
        graph_end = get_list_info(graph_end_node);


        for(ListNode_t node = get_list_first(graph_end); node != NULL; node = get_list_next(node)){
            insert_list(graph_begin, get_list_info(node));
        }
        add_graph_edge(graph_begin, edge);
        remove_list_node(_union_find, graph_end_node, delete_graph);
    }
}


