#ifndef UNION_FIND_H_
#define UNION_FIND_H_
#include "edge.h"
#include "graph.h"
typedef void* UnionFind_t;


UnionFind_t create_union_find(Graph_t _graph);

void union_union_find(UnionFind_t _union_find, Edge_t edge);


#endif
