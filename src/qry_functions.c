#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "graph.h"
#include "point.h"
#include "qry_functions.h"
#include "block.h"
#include "city.h"
#include "kdtree.h"
#include "linked_list.h"
#include "svg.h"
#include "vertex.h"

Point_t arroba_o_int(City_t _city, char *cep, char face, int num, FILE *svgFile){
    double x1, y1;
    KDTree_t blocks_tree = get_blocks_tree(_city);
    Block_t block_adress = NULL;

    get_block_from_cep(get_kd_root(blocks_tree), cep, &block_adress);
    if(block_adress == NULL){
        return NULL;
    }

    Point_t point_address = get_block_point_face(block_adress, face, num);
    x1 = get_point_x(point_address);
    y1 = get_point_y(point_address);
    print_line(x1, y1, x1, 0, "black", svgFile);
    fprintf(svgFile, "\t<text x=\"%.2f\" y=\"10\">CEP:%s FACE:%c NUM: %d</text>\n", x1, cep, face, num);
    return point_address;

    // achar o vertice mais proximo considerando um raio máximo de 100
    //Graph_t graph = get_street_graph(_city);
    //AdjList_t adj = NULL;
    //Vertex_t vertex = NULL, smaller_dist_vertex = NULL;
    //Point_t vertex_point = NULL;
    //double smaller_dist = INFINITY, x2, y2, dist;
    //for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
    //    adj = get_list_info(node);
    //    for(ListNode_t adj_node = get_list_first(graph); adj_node != NULL; adj_node = get_list_next(adj_node)){
    //        vertex = get_graph_vertex(adj);
    //        vertex_point = get_vertex_point(vertex);
    //        x2 = get_point_x(vertex_point);
    //        y2 = get_point_y(vertex_point);
    //        dist = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    //        if(dist < 0){
    //            dist = dist * (-1);
    //        }
    //        if(dist < smaller_dist){
    //            smaller_dist = dist;
    //            smaller_dist_vertex = vertex;
    //        }
    //    }
    //}
    //if(smaller_dist > 100){
    //    return NULL;
    //}
    //return vertex;
}

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
            double *key = get_block_point(block);
            fprintf(qryTXTFile, "Quadra removida ==> CEP: %s PONTO: x = %.2lf, y = %.2lf LARGURA = %.2lf, ALTURA = %.2lf ESPESSURA DA BORDA: "
                        "%s, COR DE PREENCHIMENTO %s, COR DA BORDA: %s\n", get_block_cep(block), get_block_x(block), get_block_y(block), get_block_width(block),
                        get_block_height(block), get_block_sw(block), get_block_fill(block), get_block_stroke(block));
            remove_kd_node(blocks_tree, key);
            free(get_list_info(aux));
        }
    }
    remove_list(points_inside, NULL);


    // remover vertices 
    List_t vertex_inside = get_info_inside_kd(vertex_tree, x, y, w, h);
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    char vertex_name[200];
    ListInfo_t graph_node = NULL;
    List_t edge_list = NULL;
    Edge_t edge = NULL;
    Point_t point = NULL;
    for(ListNode_t aux = get_list_first(vertex_inside); aux != NULL; aux = get_list_next(aux)){
        vertex = get_list_info(aux);
        point = get_vertex_point(vertex);
        if(is_pont_inside_rect(point, x, y, w, h)){
            fprintf(qryTXTFile, "Vertice removido ==> ID: %s X: %f Y: %f\n", get_vertex_name(vertex), get_vertex_x(vertex), get_vertex_y(vertex));
            strcpy(vertex_name, get_vertex_name(vertex));
            adj_list = get_graph_adj_list(graph, vertex_name);
            edge_list = get_graph_edges(adj_list);
            for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
                edge = get_list_info(edge_node);
                fprintf(qryTXTFile, "Aresta removida ==> NOME: %s NOME VERTICE INICIAL: %s NOME VERTICE FINAL: %s LESQ: %s LDIR: %s CMP: %f VM: %f\n", get_edge_name(edge), 
                        get_edge_begin_vertex_name(edge), get_edge_end_vertex_name(edge), get_edge_lesq(edge), get_edge_ldir(edge), get_edge_cmp(edge), get_edge_vm(edge));
            }
            graph_node = get_graph_node(graph, vertex_name);
            remove_list_node(graph, graph_node, NULL);
            delete_adj_list(adj_list);
        }
    }
    remove_list(vertex_inside, NULL);

    // remover arestas capengas
    ListNode_t edge_list_node = NULL;
    edge_list = NULL;
    edge = NULL;
    char *ending_vertex_name = NULL;

    for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        edge_list = get_graph_edges(adj_list);
        edge_list_node = get_list_first(edge_list);
        while(edge_list_node != NULL){
            edge = get_list_info(edge_list_node);
            ending_vertex_name = get_edge_end_vertex_name(edge);
            if(strcmp(ending_vertex_name, vertex_name)==0){
                ListNode_t aux = get_list_next(edge_list_node);
                fprintf(qryTXTFile, "Aresta removida ==> NOME: %s NOME VERTICE INICIAL: %s NOME VERTICE FINAL: %s LESQ: %s LDIR: %s CMP: %f VM: %f\n", get_edge_name(edge), 
                        get_edge_begin_vertex_name(edge), get_edge_end_vertex_name(edge), get_edge_lesq(edge), get_edge_ldir(edge), get_edge_cmp(edge), get_edge_vm(edge));
                remove_list_node(edge_list, edge_list_node, free);
                edge_list_node = aux;
                printf("ARESTA REMOVIDA\n");
                continue;
            }
            edge_list_node = get_list_next(edge_list_node);
        }
    }

    //TODO remover todas as arestas que começam / terminal no vertice removido, as que começam ja estão sendo removidas. e escrever no txt.
}
Graph_t rv(Graph_t graph, double x, double y, double w, double h, double f){
    Graph_t rv_Graph = create_graph_copy(graph);




}
