#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "linked_list.h"
#include "point.h"
#include "qry_utils.h"
#include "svg.h"
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

Graph_t create_dijkstra_graph(Graph_t _graph, List_t path){
    char *begin_vertex_name, *end_vertex_name;
    int index = 0;
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    Edge_t edge = NULL;

    Graph_t graph = create_graph();

    for(ListNode_t node = get_list_first(path); node != NULL; node = get_list_next(node)){
        begin_vertex_name = get_list_info(node);
        adj_list = get_graph_adj_list(_graph, begin_vertex_name);
        vertex = get_graph_vertex(adj_list);

        add_graph_vertex(graph, vertex);

        index ++;
        if(index == get_list_size(path)){
            break;
        }
        end_vertex_name = get_list_info(get_list_next(node));
        edge = get_edge_from_vertexes_adj_list(adj_list, end_vertex_name);
        if(edge == NULL){
            printf("ERRO ____ ARESTA NULA\n");
        }else{
            add_graph_edge(graph, edge);
        }
    }
    return graph;

}


void print_dijkstra_path_txt(Graph_t _graph, FILE *txtFile){
    AdjList_t adj_list = NULL;
    Edge_t edge = NULL;
    List_t edge_list = NULL;
    int index = 0;

    for(List_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        index ++;
        if(index == get_list_size(_graph)){
            return;
        }
        adj_list = get_list_info(node);
        edge_list = get_graph_edges(adj_list);
        edge = get_list_info(get_list_first(edge_list));
        fprintf(txtFile, "Siga %.2lf metros na rua %s\n", get_edge_vm(edge), get_edge_name(edge));
    }
}

void print_dijkstra_path_svg(Graph_t _graph, FILE *svgFile, int flag){
    List_t svg_path_list = create_list();
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    int index = 0;
    double x1, y1;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        vertex = get_graph_vertex(adj_list);
        if(index == 0){
            x1 = get_vertex_x(vertex);
            y1 = get_vertex_y(vertex);
        }
        Point_t point = create_point(get_vertex_x(vertex), get_vertex_y(vertex));
        insert_list(svg_path_list, point);
        index++;
    }
    print_animated_circle(x1, y1, svg_path_list, svgFile, flag);
    remove_list(svg_path_list, free);
}

