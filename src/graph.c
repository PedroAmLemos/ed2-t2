#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "linked_list.h"
#include "svg.h"
#include "edge.h"
#include "union_find.h"
#include "graph.h"
#include "reading_utility.h"
#include "vertex.h"

typedef struct AdjList{
    Vertex_t start;
    List_t edges;
}AdjList;

Graph_t create_graph(){
    return create_list();
}

Vertex_t get_graph_vertex(AdjList_t _adj_list){
    AdjList *adj_list = (AdjList*)_adj_list;
    return adj_list->start;
}

List_t get_graph_edges(AdjList_t _adj){
    AdjList *al = (AdjList*)_adj;
    return al->edges;
}

AdjList_t get_graph_adj_list(Graph_t _graph, char* vertex_name){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        AdjList* al = get_list_info(node);
        if(strcmp(vertex_name, get_vertex_name(al->start)) == 0){
            return al;
        }
    }
    return NULL;
}

Vertex_t get_graph_adj_list_vertex(Graph_t _graph, char* vertex_name){
    AdjList *al;
    al = (AdjList*) get_graph_adj_list(_graph, vertex_name);
    return al->start;
}

ListNode_t get_graph_node(Graph_t _graph, char* vertex_name){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        AdjList* al = get_list_info(node);
        if(strcmp(vertex_name, get_vertex_name(al->start)) == 0){
            return node;
        }
    }
    return NULL;
}

void add_graph_vertex(Graph_t _graph, Vertex_t _vertex){
    AdjList *adj = (AdjList *) malloc(sizeof(AdjList));
    adj->start = _vertex;
    adj->edges = create_list();
    insert_list(_graph, adj);
}

void add_graph_edge(Graph_t _graph, Edge_t _edge){
    AdjList *al = get_graph_adj_list(_graph, get_edge_begin_vertex_name(_edge));
    if(al == NULL){
        return;
    }
    insert_list(al->edges, _edge);
}

void delete_adj_list(AdjList_t _adj){
    AdjList *al = (AdjList*) _adj;
    // TODO see this
    remove_list(al->edges, free);
    free(get_vertex_point(al->start));
    free(al->start);
    free(_adj);
}

void delete_graph(Graph_t _graph){
    remove_list(_graph, NULL);
}

void delete_full_graph(Graph_t _graph){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        delete_adj_list(get_list_info(node));
    }
    delete_graph(_graph);
}

void delete_graph_lists(Graph_t _graph){
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        remove_list(get_list_info(node), NULL);
    }

    remove_list(_graph, NULL);
}

Graph_t create_graph_copy(Graph_t graph){
    Graph_t copy = create_graph();
    AdjList *adj = NULL;
    ListNode_t edge_list = NULL;
    Vertex_t vertex = NULL;
    for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
        adj = (AdjList *) get_list_info(node);
        edge_list = adj->edges;
        vertex = adj->start;
        add_graph_vertex_copy(copy, vertex);
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            add_graph_edge_copy(copy, get_list_info(edge_node));
        }
    }
    return copy;
}

void clean_adj_edges(AdjList_t _adj){
    AdjList *adj = (AdjList *) _adj;
    remove_list(adj->edges, free);
    adj->edges = create_list();
}

void add_graph_edge_copy(Graph_t _graph, Edge_t _edge){
    AdjList *al = get_graph_adj_list(_graph, get_edge_begin_vertex_name(_edge));
    if(al == NULL){
        return;
    }
    Edge_t edge = NULL;
    edge = create_edge(get_edge_name(_edge), get_edge_begin_vertex_name(_edge), get_edge_end_vertex_name(_edge), get_edge_ldir(_edge), get_edge_lesq(_edge), get_edge_cmp(_edge), get_edge_vm(_edge));
    insert_list(al->edges, edge);
}

void add_graph_vertex_copy(Graph_t _graph, Vertex_t _vertex){
    AdjList *adj = (AdjList *) malloc(sizeof(AdjList));
    Vertex_t copy = create_vertex(get_vertex_name(_vertex), get_vertex_x(_vertex), get_vertex_y(_vertex));
    adj->start = copy;
    adj->edges = create_list();
    insert_list(_graph, adj);
}

int on_adj_list(AdjList_t _adj, char *begin, char *end){
    AdjList *adj = (AdjList *) _adj;
    List_t edge_list = adj->edges;
    Edge_t edge = NULL;
    char *begin_vertex = NULL;
    char *ending_vertex = NULL;
    for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
        edge = get_list_info(edge_node);
        begin_vertex = get_edge_begin_vertex_name(edge);
        ending_vertex = get_edge_end_vertex_name(edge);
        if(strcmp(begin_vertex, begin) == 0 && strcmp(ending_vertex, end) == 0){
            return 1;
        }
    }
    return 0;
}

Graph_t agm_kruskal(Graph_t _graph){

    List_t edges = create_list();
    List_t edge_list = NULL;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        edge_list = get_graph_edges(get_list_info(node));
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            insert_list(edges, get_list_info(edge_node));
        }
    }

    quick_sort_edge_list(edges, 0, get_list_size(edges)-1);

    UnionFind_t union_find = create_union_find(_graph);
    for(ListNode_t node = get_list_first(edges); node != NULL; node = get_list_next(node)){
        union_union_find(union_find, get_list_info(node));
    }

    Graph_t agm = NULL;
    agm = create_graph_copy(get_list_info(get_list_first(union_find)));

    remove_list(union_find, union_find_remove_aux);
    remove_list(edges, NULL);

    return agm;
}

void union_find_remove_aux(Graph_t _graph){
    AdjList_t adj_list = NULL;
    List_t edge_list = NULL;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        edge_list = get_graph_edges(adj_list);
        remove_list(edge_list, NULL);
        free(adj_list);
    }
    remove_list(_graph, NULL);
}


Vertex_t get_adj_list_vertex(AdjList_t _adj_list){
    AdjList *adj = (AdjList *) _adj_list;
    return adj->start;
}


Edge_t get_edge_from_vertexes_adj_list(AdjList_t _adj_list, char *ending_vertex){
    List_t edge_list = get_graph_edges(_adj_list);
    Edge_t edge = NULL;
    for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
        edge = get_list_info(edge_node);
        if(strcmp(ending_vertex, get_edge_end_vertex_name(edge))==0){
            return edge;
        }
    }
    return NULL;
}

Edge_t get_edge_from_vertexes(Graph_t _graph, char* begin_vertex, char *ending_vertex){
    AdjList_t adj_list = NULL;
    List_t edge_list = NULL;
    Edge_t edge = NULL;
    adj_list = get_graph_adj_list(_graph, begin_vertex);
    edge_list = get_graph_edges(adj_list);
    for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
        edge = get_list_info(edge_node);
        if(strcmp(ending_vertex, get_edge_end_vertex_name(edge))==0){
            return edge;
        }
    }
    return NULL;
}

void dfs(Graph_t _graph, Graph_t _agm_graph, HashTable_t vertex_table, ListNode_t adj_list_node, int cd, double f_in, double f){

    AdjList_t adj_list = get_list_info(adj_list_node);
    List_t edges = get_graph_edges(adj_list);
    ListNode_t next_adj_node = NULL;
    Vertex_t vertex = get_graph_vertex(adj_list);

    insert_hash(vertex_table, get_vertex_name(vertex), vertex);

    Edge_t edge = NULL;
    Edge_t to_change_edge = NULL;

    for(ListNode_t node = get_list_first(edges); node != NULL; node = get_list_next(node)){
        edge = get_list_info(node);
        to_change_edge = get_edge_from_vertexes(_graph, get_edge_begin_vertex_name(edge), get_edge_end_vertex_name(edge));
        set_edge_vm(to_change_edge, get_edge_vm(edge)*f);

        next_adj_node = get_graph_node(_agm_graph, get_edge_end_vertex_name(edge));
        if(f+f_in < 1)
            f = f+f_in;
        if(get_info_from_key(vertex_table, get_vertex_name(get_graph_vertex(get_list_info(next_adj_node))))== NULL){
            dfs(_graph, _agm_graph, vertex_table, next_adj_node, cd+1, f_in, f);        
        }
    }
}

List_t dijkstra(Graph_t _graph, Vertex_t begin, Vertex_t end, double *total_dist, double get_weight(Edge_t _edge)){
    char *name_begin = get_vertex_name(begin), *name_end = get_vertex_name(end);
    List_t remaining = create_list();
    HashTable_t distance = create_hash_table(500);
    HashTable_t previous = create_hash_table(500);

    double *aux = malloc(sizeof(double));
    *aux = 0;


    insert_hash(distance, name_begin, aux);
    for(Node_t *node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        insert_list(remaining, get_vertex_name(get_graph_vertex(get_list_info(node))));
    }


    while(1){
        AdjList_t adj_list = get_graph_adj_list(_graph, name_begin);
        double *previous_dist = (double *) get_info_from_key(distance, name_begin);
        for(Node_t aux = get_list_first(get_graph_edges(adj_list)); aux != NULL; aux = get_list_next(aux)){
            Edge_t edge = get_list_info(aux);
            if(get_edge_state(edge)){
                continue;
            }

            char *id_aux = get_edge_end_vertex_name(edge); 
            double *dist = get_info_from_key(distance, id_aux);

            if(is_string_in_list(remaining, name_begin)){
                if(dist == NULL){
                    double *dist_temp = malloc(sizeof(double));
                    *dist_temp = get_weight(edge) + *previous_dist;
                    insert_hash(distance, id_aux, dist_temp);
                    char *temp_id = malloc(sizeof(char) * (strlen(name_begin)) + 500);
                    strcpy(temp_id, name_begin);
                    insert_hash(previous, id_aux, temp_id);
                }else if(*dist > get_weight(edge) + *previous_dist){
                    *dist = get_weight(edge) + *previous_dist;
                    free(get_info_from_key(previous, id_aux));
                    char *temp_id = malloc(sizeof(char) * (strlen(name_begin) + 1));
                    strcpy(temp_id, name_begin);
                    change_value(previous, id_aux, temp_id);
                }
            }
        }
        if(strcmp(name_begin, name_end) == 0){
            *total_dist = *(double*)get_info_from_key(distance, name_end);
            break;
        }
        double small;
        int flag = 1;
        char previous_id[100];
        strcpy(previous_id, name_begin);
        Node_t node = get_list_first(remaining);
        while(node != NULL){
            if(strcmp(get_list_info(node), previous_id) == 0){
                Node_t visited = node;
                node = get_list_next(node);
                remove_list_node(remaining, visited, NULL);
                continue;
            }
            double *value = get_info_from_key(distance, get_list_info(node));
            if(value != NULL && (flag || small > *value)) {
                small = *value;
                name_begin = get_list_info(node);
                flag = 0;
            }
            node = get_list_next(node);
        }
        if(flag){
            *total_dist = 0;
            delete_hash_table(distance, 0);
            delete_hash_table(previous, 0);
            remove_list(remaining, NULL);
            return NULL;
        }
    }
    List_t path = create_list();
    while(name_end != NULL){
        char *path_aux = malloc(sizeof(char) * (strlen(name_end)+1));
        strcpy(path_aux, name_end);
        insert_list(path, path_aux);
        name_end = get_info_from_key(previous, name_end);
    }
    delete_hash_table(distance, 1);
    delete_hash_table(previous, 1);
    remove_list(remaining, NULL);

    List_t inverted_path = reverse_linked_list(path);

    remove_list(path, NULL);

    return inverted_path;
}
