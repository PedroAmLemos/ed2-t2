#ifndef QRY_UTILS_H_
#define QRY_UTILS_H_
#include "graph.h"
#include "linked_list.h"
#include "vertex.h"

// Retorna se um nome está em uma dada lista
int is_name_in_list(List_t _list, char *name);

// Retorna o vertice mais proximo de um ponto passado
Vertex_t get_closest_vertex(Graph_t _graph, Point_t point);

// Recebe uma lista com um caminho e retorna um grafo com os vértices e arestas que compoem esse caminho
Graph_t create_dijkstra_graph(Graph_t _graph, List_t path);

// Recebe um grafo e imprime o trajeto em um txt
void print_dijkstra_path_txt(Graph_t _graph, FILE *txtFile);

// Recebe um grafo e imprime o trajeto em um svg
void print_dijkstra_path_svg(Graph_t _graph, FILE *svgFile, int flag);

#endif

