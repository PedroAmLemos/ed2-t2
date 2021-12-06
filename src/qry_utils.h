#ifndef QRY_UTILS_H_
#define QRY_UTILS_H_
#include "graph.h"
#include "linked_list.h"
#include "vertex.h"

int is_name_in_list(List_t _list, char *name);

Vertex_t get_closest_vertex(Graph_t _graph, Point_t point);

Graph_t create_dijkstra_graph(Graph_t _graph, List_t path);

void print_dijkstra_path_txt(Graph_t _graph, FILE *txtFile);

void print_dijkstra_path_svg(Graph_t _graph, FILE *svgFile, int flag);

#endif

