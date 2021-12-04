#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "qry_utils.h"
#include "vertex.h"

int is_name_in_list(List_t _list, char *name){
    for(ListNode_t node = get_list_first(_list); node != NULL; node = get_list_next(node)){
        if(strcmp(name, get_list_info(node))==0){
            return 1;
        }
    }
    return 0;
}

Vertex_t get_closest_vertex(Graph_t _graph, Point_t point){
    // achar o vertice mais proximo considerando um raio máximo de 100
    double x1 = get_point_x(point), y1 = get_point_y(point);
    Graph_t graph = _graph;
    AdjList_t adj = NULL;
    Vertex_t vertex = NULL, smaller_dist_vertex = NULL;
    Point_t vertex_point = NULL;
    double smaller_dist = 100, x2, y2, dist;
    for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
        adj = get_list_info(node);
        vertex = get_graph_vertex(adj);
        vertex_point = get_vertex_point(vertex);
        x2 = get_point_x(vertex_point);
        y2 = get_point_y(vertex_point);
        dist = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
        if(dist < smaller_dist){
            smaller_dist = dist;
            smaller_dist_vertex = vertex;
        }
    }
    if(smaller_dist == 100){
        return NULL;
    }
    
    return smaller_dist_vertex;
}
