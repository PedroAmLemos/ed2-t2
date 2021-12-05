#include <string.h>
#include <stdlib.h>
#include "edge.h"
#include "graph.h"
#include "linked_list.h"
#include "vertex.h"


typedef struct Edge{
    char name[100];
    char begin_vertex_name[100];
    char end_vertex_name[100];
    char ldir[100];
    char lesq[100];
    double cmp;
    double vm;
    int is_closed;
}Edge;

Edge_t create_edge(char* name, char* begin_vertex_name, char* end_vertex_name, char* ldir, char* lesq, double cmp, double vm){
    Edge* edge = (Edge*) malloc(sizeof(Edge));
    strcpy(edge->begin_vertex_name, begin_vertex_name);
    strcpy(edge->end_vertex_name, end_vertex_name);
    strcpy(edge->name, name);
    strcpy(edge->ldir, ldir);
    strcpy(edge->lesq, lesq);
    edge->cmp = cmp;
    edge->vm = vm;
    edge->is_closed = 0;
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


int partition(List_t _list, int begin, int end){
    double pivot = get_edge_cmp(get_list_info(get_list_last(_list)));
    int pIndex = begin;

    for(int i = begin; i < end; i++){
        if(get_edge_cmp(get_list_info(get_list_index_node(_list, i))) <= pivot){
            swap_list_info(get_list_index_node(_list, i), get_list_index_node(_list, pIndex));
            pIndex++;
        }
    }
    swap_list_info(get_list_index_node(_list, pIndex), get_list_index_node(_list, end));
    return pIndex;
}

void quick_sort_edge_list(List_t _list, int begin, int end){
    if(begin >= end)
        return;
    int pivot = partition(_list, begin, end);
    quick_sort_edge_list(_list, begin, pivot-1);
    quick_sort_edge_list(_list, pivot+1, end);
}

Edge_t create_edge_copy(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    Edge *result = create_edge(edge->name, edge->begin_vertex_name, edge->end_vertex_name, edge->ldir, edge->lesq, edge->cmp, edge->vm);
    return result;
}

void print_edge_txt(Edge_t _edge, FILE *txtFILE){
    Edge *edge = (Edge*) _edge;
    fprintf(txtFILE, "ArestaAGM >>>> NOME: %s VERTICE INICIAL: %s VERTICE FINAL: %s VM: %f CMP: %f\n", edge->name, edge->begin_vertex_name, edge->end_vertex_name, edge->vm, edge->cmp);
}

void set_edge_vm(Edge_t _edge, double new_vm){
    if(_edge == NULL) return;
    Edge *edge = (Edge*) _edge;
    edge->vm = new_vm;
}

void set_edge_state(Edge_t _edge, int state){
    Edge *edge = (Edge*) _edge;
    edge->is_closed = state;
}
int get_edge_state(Edge_t _edge){
    Edge *edge = (Edge*) _edge;
    return edge->is_closed;
}

