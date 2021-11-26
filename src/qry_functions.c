#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "hash_table.h"
#include "reading_utility.h"
#include "edge.h"
#include "graph.h"
#include "point.h"
#include "qry_functions.h"
#include "block.h"
#include "city.h"
#include "kdtree.h"
#include "linked_list.h"
#include "qry_utils.h"
#include "svg.h"
#include "union_find.h"
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
    double *key;
    List_t points_inside = get_info_inside_kd(blocks_tree, x, y, w, h);
    for(ListNode_t aux = get_list_first(points_inside); aux != NULL; aux = get_list_next(aux)){
        if(is_block_inside_rect(get_list_info(aux), x, y, w, h)){
            block = get_list_info(aux);
            key = get_block_point(block);
            fprintf(qryTXTFile, "Quadra removida ==> CEP: %s PONTO: x = %.2lf, y = %.2lf LARGURA = %.2lf, ALTURA = %.2lf ESPESSURA DA BORDA: "
                        "%s, COR DE PREENCHIMENTO %s, COR DA BORDA: %s\n", get_block_cep(block), get_block_x(block), get_block_y(block), get_block_width(block),
                        get_block_height(block), get_block_sw(block), get_block_fill(block), get_block_stroke(block));
            remove_kd_node(blocks_tree, key);
            free(get_list_info(aux));
        }
    }
    remove_list(points_inside, NULL);

    // remover vertices e suas arestas
    char vertex_name[200];
    List_t vertex_inside      = get_info_inside_kd(vertex_tree, x, y, w, h);
    AdjList_t adj_list        = NULL;
    Vertex_t vertex           = NULL;
    List_t edge_list          = NULL;
    Edge_t edge               = NULL;
    Point_t point             = NULL;
    ListNode_t edge_list_node = NULL;
    char *ending_vertex_name  = NULL;

    for(ListNode_t aux = get_list_first(vertex_inside); aux != NULL; aux = get_list_next(aux)){
        vertex = get_list_info(aux);
        point = get_vertex_point(vertex);
        strcpy(vertex_name, get_vertex_name(vertex));
        if(is_pont_inside_rect(point, x, y, w, h)){
            adj_list = get_graph_adj_list(graph, vertex_name);
            edge_list = get_graph_edges(adj_list);
            for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
                edge = get_list_info(edge_node);
                fprintf(qryTXTFile, "Aresta removida ==> NOME: %s NOME VERTICE INICIAL: %s NOME VERTICE FINAL: %s LESQ: %s LDIR: %s CMP: %f VM: %f\n", get_edge_name(edge), 
                        get_edge_begin_vertex_name(edge), get_edge_end_vertex_name(edge), get_edge_lesq(edge), get_edge_ldir(edge), get_edge_cmp(edge), get_edge_vm(edge));
            }
            clean_adj_edges(adj_list);
        }
        // remover arestas capengas
        edge_list_node = NULL;
        edge_list = NULL;
        edge = NULL;
        ending_vertex_name = NULL;

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
                    continue;
                }
                edge_list_node = get_list_next(edge_list_node);
            }
        }
    }
    remove_list(vertex_inside, NULL);


}
void rv(City_t _city, double x, double y, double w, double h, double f, FILE *qrySVGFile, FILE* qryTXTFile){
    Graph_t graph            = get_street_graph(_city);
    Graph_t carlos           = create_graph();
    List_t vertex_names      = create_list();
    List_t edge_list         = NULL;
    Vertex_t vertex          = NULL;
    Edge_t edge              = NULL;
    Edge_t edge_aux          = NULL;
    Point_t point            = NULL;
    AdjList_t adj_list       = NULL;
    char *name               = NULL;
    char *ending_vertex_name = NULL;
    char *begin_vertex_name  = NULL;
    AdjList_t adj_list_aux   = NULL;

    print_rectangle_dashed(x, y, w, h, qrySVGFile);

    // criar o novo grafo
    for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        vertex = get_graph_vertex(adj_list);
        edge_list = get_graph_edges(adj_list);
        point = get_vertex_point(vertex);
        if(is_pont_inside_rect(point, x, y, w, h)){
            name = copy(get_vertex_name(get_graph_vertex(adj_list)));
            insert_list(vertex_names, name);
        }
    }

    for(ListNode_t node = get_list_first(graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        vertex = get_graph_vertex(adj_list); edge_list = get_graph_edges(adj_list);
        point = get_vertex_point(vertex);
        if(is_pont_inside_rect(point, x, y, w, h)){
            add_graph_vertex_copy(carlos, vertex);
            for(ListNode_t node_node = get_list_first(edge_list); node_node != NULL; node_node = get_list_next(node_node)){
                ending_vertex_name = get_edge_end_vertex_name(get_list_info(node_node));
                if(is_name_in_list(vertex_names, ending_vertex_name)){
                    add_graph_edge_copy(carlos, get_list_info(node_node));
                }
            }
        }
    }
    remove_list(vertex_names, free);

    for(ListNode_t node = get_list_first(carlos); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        edge_list = get_graph_edges(adj_list);
        for(ListNode_t edge_list_node = get_list_first(edge_list); edge_list_node != NULL; edge_list_node = get_list_next(edge_list_node)){
            edge = get_list_info(edge_list_node);
            ending_vertex_name = get_edge_end_vertex_name(edge);
            begin_vertex_name = get_edge_begin_vertex_name(edge);
            adj_list_aux = get_graph_adj_list(graph, ending_vertex_name);
            if(!on_adj_list(adj_list_aux, ending_vertex_name, begin_vertex_name) && strcmp(ending_vertex_name, begin_vertex_name) != 0){
                edge_aux = create_edge(get_edge_name(edge), get_edge_end_vertex_name(edge), get_edge_begin_vertex_name(edge), "-", "-", get_edge_vm(edge), get_edge_vm(edge)); 
                add_graph_edge(carlos, edge_aux);
            }
        }
    }


    Graph_t agm;
    agm = agm_kruskal(carlos);
    delete_full_graph(carlos);
    print_graph_agm(agm, qrySVGFile);
    print_thick_vertex(get_graph_vertex(get_list_info(get_list_first(agm))), qrySVGFile);

    List_t edges_aux = create_list();
    for(ListNode_t node = get_list_first(agm); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        edge_list = get_graph_edges(adj_list);
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            edge = get_list_info(edge_node);
            insert_list(edges_aux, create_edge(get_edge_name(edge), get_edge_end_vertex_name(edge), 
                        get_edge_begin_vertex_name(edge), "-", "-", get_edge_cmp(edge), get_edge_vm(edge)));
            print_edge_txt(edge, qryTXTFile);
        }
    }
    for(ListNode_t node = get_list_first(edges_aux); node != NULL; node = get_list_next(node)){
        add_graph_edge(agm, get_list_info(node));
    }
    HashTable_t vertexes_table = create_hash_table(get_list_size(agm));

    dfs(graph, agm, vertexes_table, get_list_first(agm), 0, f, f);
    delete_hash_table(vertexes_table, 0);
    remove_list(edges_aux, NULL);
    delete_full_graph(agm);
}


void cx(City_t city, double limiar, FILE *qrySVGFile, FILE *qryTXTFile){
    Graph_t streets_graph = get_street_graph(city);
    Graph_t streets_graph_copy = create_graph_copy(streets_graph);
    Graph_t graph = NULL;
    List_t edges = create_list();
    List_t edge_list = NULL;




    //Vertex_t begin = NULL;
    //Vertex_t end = NULL;
    for(ListNode_t node = get_list_first(streets_graph); node != NULL; node = get_list_next(node)){
        edge_list = get_graph_edges(get_list_info(node));
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            if(get_edge_vm(get_list_info(edge_node))>= limiar){
                insert_list(edges, get_list_info(edge_node));
            }
            //else{
            //    begin = get_graph_adj_list_vertex(streets_graph, get_edge_begin_vertex_name(get_list_info(edge_node)));
            //    end = get_graph_adj_list_vertex(streets_graph, get_edge_end_vertex_name(get_list_info(edge_node)));
            //    //print_line(get_vertex_x(begin), get_vertex_y(begin), get_vertex_x(end), get_vertex_y(end), "red", teste);
            //}
        }
    }

    UnionFind_t sub_graphs = create_union_find(streets_graph_copy);

    for(ListNode_t node = get_list_first(edges); node != NULL; node = get_list_next(node)){
        union_union_find(sub_graphs, get_list_info(node));
    }

    Vertex_t vertex = NULL;
    AdjList_t adj_list = NULL;
    int index = 0;
    char colors[][50] = {"blue", "green", "yellow", "pink", "purple", "grey", "plum", "seagreen", "indigo", "peru", 
        "aliceblue", "antiquewhite", "aquamarine", "azure", "beige", "bisque", "blanchedalmond", "blueviolet", "brown", "coral"};
// cadetblue chartreuse		chocolate	cornflowerblue		cornsilk		crimson	cyan	darkblue		darkcyan		darkgoldenrod	darkgray	darkgreen		darkgrey		darkkhaki	darkmagenta	darkolivegreen		darkorange		darkorchid	darkred	darksalmon		darkseagreen		darkslateblue	darkslategray	darkslategrey		darkturquoise		darkviolet	deeppink	deepskyblue		dimgray		dimgrey	dodgerblue	firebrick		floralwhite		forestgreen	fuchsia	gainsboro		ghostwhite		gold	goldenrod	gray(16)		green(16)		greenyellow	grey(16)	honeydew		hotpink		indianred	indigo	ivory		khaki		lavender	lavenderblush	lawngreen		lemonchiffon		lightblue	lightcoral	lightcyan		lightgoldenrodyellow		lightgray	lightgreen	lightgrey		lightpink		lightsalmon	lightseagreen	lightskyblue		lightslategray(Hex3)		lightslategrey(Hex3)	lightsteelblue	lightyellow				limegreen	linen	magenta		maroon(16)		mediumaquamarine	mediumblue	mediumorchid		mediumpurple		mediumseagreen	mediumslateblue	mediumspringgreen		mediumturquoise		mediumvioletred	midnightblue	mintcream		mistyrose		moccasin	navajowhite	navy(16)		oldlace		olive(16)	olivedrab	orange		orangered		orchid	palegoldenrod	palegreen		paleturquoise		palevioletred	papayawhip	peachpuff		peru		pink	plum	powderblue		purple(16)			rosybrown	royalblue		saddlebrown		salmon	sandybrown	seagreen		seashell		sienna	silver(16)	skyblue		slateblue		slategray	slategrey	snow		springgreen		steelblue	tan	teal(16)		thistle		tomato	turquoise	violet		wheat			whitesmoke	yellowgreen
    for(ListNode_t node = get_list_first(sub_graphs); node != NULL; node = get_list_next(node)){
        graph = get_list_info(node);
        for(ListNode_t node_aux = get_list_first(graph); node_aux != NULL; node_aux = get_list_next(node_aux)){
            adj_list = get_list_info(node_aux);
            vertex = get_graph_vertex(adj_list);
            print_circle(get_vertex_x(vertex), get_vertex_y(vertex), 15, colors[index], colors[index], "0", qrySVGFile);
        }
        index++;
    }
    remove_list(edges, NULL);
    delete_full_graph(streets_graph_copy);
    remove_list(sub_graphs, union_find_remove_aux);

}
