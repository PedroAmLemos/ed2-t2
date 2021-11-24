#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include "hash_table.h"
#include "linked_list.h"
#include "vertex.h"
#include "edge.h"


typedef void* Graph_t;
typedef void* AdjList_t;


Graph_t create_graph();

Vertex_t get_graph_vertex(AdjList_t _adj_list);

List_t get_graph_edges(AdjList_t _adj);

AdjList_t get_graph_adj_list(Graph_t _graph, char* vertex_name);

AdjList_t get_graph_adj_list_vertex(Graph_t _graph, char* vertex_name);

ListNode_t get_graph_node(Graph_t _graph, char* vertex_name);

void add_graph_vertex(Graph_t _graph, Vertex_t _vertex);

void add_graph_edge(Graph_t _graph, Edge_t _edge);

void delete_adj_list(AdjList_t _adj);

void delete_graph(Graph_t _graph);

void delete_full_graph(Graph_t _graph);

Graph_t create_graph_copy(Graph_t graph);

void clean_adj_edges(AdjList_t _adj);

void add_graph_edge_copy(Graph_t _graph, Edge_t _edge);

void add_graph_vertex_copy(Graph_t _graph, Vertex_t _vertex);

int on_adj_list(AdjList_t _adj, char *begin, char *end);

Graph_t agm_kruskal(Graph_t _graph);

void union_find_remove_aux(Graph_t _graph);

void dfs(Graph_t _graph, Graph_t _agm_graph, HashTable_t vertex_table, ListNode_t adj_list_node, int cd, double f_in, double f);
#endif

