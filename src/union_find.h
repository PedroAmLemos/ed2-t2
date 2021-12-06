#ifndef UNION_FIND_H_
#define UNION_FIND_H_
#include "edge.h"
#include "graph.h"
typedef void* UnionFind_t;

// Cria uma lista union find
UnionFind_t create_union_find(Graph_t _graph);

// executa o comando union find da estrutura
void union_union_find(UnionFind_t _union_find, Edge_t edge);


#endif
