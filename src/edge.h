#ifndef EDGE_H_
#define EDGE_H_

typedef void* Edge_t;

Edge_t createAresta(char* name, char* begin_vertex_name, char* end_vertex_name, char* ldir, char* lesq, double cmp, double vm);

char *get_edge_name(Edge_t _edge);

char *get_edge_begin_vertex_name(Edge_t _edge);

char *get_edge_end_vertex_name(Edge_t _edge);

char *get_edge_ldir(Edge_t _edge);

char *get_edge_lesq(Edge_t _edge);

double get_edge_cmp(Edge_t _edge);

double get_edge_vm(Edge_t _edge);

double get_edge_time(Edge_t _edge);

#endif
