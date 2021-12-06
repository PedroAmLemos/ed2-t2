#ifndef EDGE_H_
#define EDGE_H_

#include "linked_list.h"
#include <stdio.h>
typedef void* Edge_t;

// Cria e insere os valores passados para uma nova aresta
Edge_t create_edge(char* name, char* begin_vertex_name, char* end_vertex_name, char* ldir, char* lesq, double cmp, double vm);

// Cria uma copia e insere os valores de uma aresta passada
Edge_t create_edge_copy(Edge_t _edge);

// Recebe uma lista de arestas e execura o quick sort
void quick_sort_edge_list(List_t _list, int begin, int end);

// Recebe uma aresta e um arquivo de texto, imprime os atributos da aresta no arquivo
void print_edge_txt(Edge_t _edge, FILE *txtFILE);


// Getters: Retorna o atributo do título da função.
// Setters: Altera o valor, do atributo do título da função, de uma aresta passada
char *get_edge_name(Edge_t _edge);
char *get_edge_begin_vertex_name(Edge_t _edge);
char *get_edge_end_vertex_name(Edge_t _edge);
char *get_edge_ldir(Edge_t _edge);
char *get_edge_lesq(Edge_t _edge);
double get_edge_cmp(Edge_t _edge);
double get_edge_vm(Edge_t _edge);
double get_edge_time(Edge_t _edge);
int get_edge_state(Edge_t _edge);
void set_edge_vm(Edge_t _edge, double new_vm);
void set_edge_state(Edge_t _edge, int state);

#endif
