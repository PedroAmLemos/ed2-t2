#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include "hash_table.h"
#include "linked_list.h"
#include "vertex.h"
#include "edge.h"


typedef void* Graph_t;
typedef void* AdjList_t;

// Cria um grafo vazio
Graph_t create_graph();


// Desaloca e memoria de uma lista de adjacencias passada
void delete_adj_list(AdjList_t _adj);

// Desaloca a memória do grafo
void delete_graph(Graph_t _graph);

// Desaloca amemória do grafo e seus componentes
void delete_full_graph(Graph_t _graph);

// Cria uma cópia do grafo passado
Graph_t create_graph_copy(Graph_t graph);

// Limpa os elementos de uma lista de adjacencias
void clean_adj_edges(AdjList_t _adj);

// Recebe um nome de inicio e um de fim e retorna se existe uma aresta com esses parametros na lista de adjacencias passada
int on_adj_list(AdjList_t _adj, char *begin, char *end);

// Executa o algoritmo de kruskal em um grafo passado. Retorna um novo grafo com o a agm
Graph_t agm_kruskal(Graph_t _graph);

// Uma função auxiliar para desalocar memória da estrutura union find
void union_find_remove_aux(Graph_t _graph);

// Executa o algoritmo de busca em profundidade para execução de uma parte do comando rv
void dfs(Graph_t _graph, Graph_t _agm_graph, HashTable_t vertex_table, ListNode_t adj_list_node, int cd, double f_in, double f);

// Executa o algoritmo de dijkstra, retorna uma lista com o nome dos vertices no trajeto
List_t dijkstra(Graph_t _graph, Vertex_t begin, Vertex_t end, double *total_dist, double get_weight(Edge_t _edge));

// Desaloca memória das listas no grafo
void delete_graph_lists(Graph_t _graph);

// Getters: Retorna o atributo do título da função.
// Adders: Insere o valor, do atributo do título da função, em um grafo passado
Vertex_t get_graph_vertex(AdjList_t _adj_list);
List_t get_graph_edges(AdjList_t _adj);
AdjList_t get_graph_adj_list(Graph_t _graph, char* vertex_name);
Vertex_t get_graph_adj_list_vertex(Graph_t _graph, char* vertex_name);
ListNode_t get_graph_node(Graph_t _graph, char* vertex_name);
Edge_t get_edge_from_vertexes(Graph_t _graph, char* begin_vertex, char *ending_vertex);
Edge_t get_edge_from_vertexes_adj_list(AdjList_t _adj_list, char *ending_vertex);
void add_graph_vertex(Graph_t _graph, Vertex_t _vertex);
void add_graph_edge(Graph_t _graph, Edge_t _edge);
void add_graph_edge_copy(Graph_t _graph, Edge_t _edge);
void add_graph_vertex_copy(Graph_t _graph, Vertex_t _vertex);
#endif

