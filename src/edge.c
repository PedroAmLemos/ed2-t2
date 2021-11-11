#include <string.h>
#include <stdlib.h>
#include "edge.h"
#include "graph.h"
#include "vertex.h"


typedef struct Edge{
    char name[100];
    char begin_vertex_name[100];
    char end_vertex_name[100];
    char ldir[100];
    char lesq[100];
    double cmp;
    double vm;
}Edge;

Edge_t createAresta(char* name, char* begin_vertex_name, char* end_vertex_name, char* ldir, char* lesq, double cmp, double vm){
    Edge* edge = (Edge*) malloc(sizeof(Edge));
    strcpy(edge->begin_vertex_name, begin_vertex_name);
    strcpy(edge->end_vertex_name, end_vertex_name);
    strcpy(edge->name, name);
    strcpy(edge->ldir, ldir);
    strcpy(edge->lesq, lesq);
    edge->cmp = cmp;
    edge->vm = vm;
    return edge;
}

char *get_edge_name(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->name;
}

char *get_edge_begin_vertex_name(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->begin_vertex_name;
}
char *get_edge_end_vertex_name(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->end_vertex_name;
}

char *get_edge_ldir(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->ldir;
}

char *get_edge_lesq(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->lesq;
}

double get_edge_cmp(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->cmp;
}

double get_edge_vm(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->vm;
}

double get_edge_time(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->cmp / edge->vm;
}


