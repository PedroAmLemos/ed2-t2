#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "qry_functions.h"
#include "block.h"
#include "city.h"
#include "kdtree.h"
#include "linked_list.h"
#include "svg.h"
#include "vertex.h"

void catac(City_t _city, double x, double y, double w, double h, FILE *qrySVGFile, FILE *qryTXTFile){
    KDTree_t blocks_tree = get_blocks_tree(_city);
    KDTree_t vertex_tree = get_vertex_tree(_city);
    Graph_t graph = get_street_graph(_city);
    Block_t block;
    print_rectangle(x, y, w, h, "#AB37C8", "#AA0044", qrySVGFile);


    // remover quadras
    List_t points_inside = get_info_inside_kd(blocks_tree, x, y, w, h);
    for(ListNode_t aux = get_list_first(points_inside); aux != NULL; aux = get_list_next(aux)){
        if(is_block_inside_rect(get_list_info(aux), x, y, w, h)){
            block = get_list_info(aux);
            double *key = get_block_point(get_list_info(aux));

            fprintf(qryTXTFile, "Quadra removida\n");
            print_block_txt(block, qryTXTFile);
            remove_kd_node(blocks_tree, key);
            free(get_list_info(aux));
        }
    }
    remove_list(points_inside, NULL);


    // remover vertices e arestas
    List_t vertex_inside = get_info_inside_kd(vertex_tree, x, y, w, h);
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    Point_t point = NULL;
    char *vertex_name = NULL;
    for(ListNode_t aux = get_list_first(vertex_inside); aux != NULL; aux = get_list_next(aux)){
        vertex = get_list_info(aux);
        point = get_vertex_point(vertex);
        if(is_pont_inside_rect(point, x, y, w, h)){
            vertex_name = get_vertex_name(vertex);
            adj_list = get_graph_adj_list(graph, vertex_name);
            ListInfo_t graph_node = get_graph_node(graph, vertex_name);
            remove_list_node(graph, graph_node, NULL);
            delete_adj_list(adj_list);
        }
    }
    remove_list(vertex_inside, NULL);
}
