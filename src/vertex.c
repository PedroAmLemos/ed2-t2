#include <string.h>
#include <stdlib.h>
#include "vertex.h"
#include "point.h"

typedef struct Vertex{
    char id[200];
    Point_t point;
}Vertex;

Vertex_t create_vertex(char *name, double x, double y){
    Vertex *vertex = (Vertex*)malloc(sizeof(Vertex));
    strcpy(vertex->id, name);
    vertex->point = create_point(x, y);
    return vertex;
}

char *get_vertex_name(Vertex_t _vertex){
    Vertex *vertex = (Vertex*) _vertex;
    return vertex->id;
}

Point_t get_vertex_point(Vertex_t _vertex){
    Vertex *vertex = (Vertex*) _vertex;
    return vertex->point;
}

double get_vertex_x(Vertex_t _vertex){
    Vertex *vertex = (Vertex*) _vertex;
    return get_point_x(vertex->point);
}

double get_vertex_y(Vertex_t _vertex){
    Vertex *vertex = (Vertex*) _vertex;
    return get_point_y(vertex->point);
}
