#ifndef VERTEX_H_
#define VERTEX_H_
#include "point.h"

typedef void* Vertex_t;

char *get_vertex_name(Vertex_t _vertex);

Vertex_t create_vertex(char *name, double x, double y);

char *get_vertex_name(Vertex_t _vertex);

Point_t get_vertex_point(Vertex_t _vertex);

double get_vertex_x(Vertex_t _vertex);

double get_vertex_y(Vertex_t _vertex);

#endif
