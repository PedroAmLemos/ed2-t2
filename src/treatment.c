#include <stdio.h>
#include <string.h>
#include "city.h"
#include "edge.h"
#include "qry.h"
#include "svg.h"
#include "treatment.h"
#include "kdtree.h"
#include "block.h"


void main_treatment(FILE *geoFile, FILE *qryFile, FILE *viaFile, FILE *geoSVGFile, FILE *qrySVGFile, FILE *qryTXTFile){
    double x = 0, y = 0, w = 0, h = 0, point[2]; 
    char aux[5], cep[200], cfill[200], cstrk[200], sw[200];
    Block_t block = NULL;
    City_t city = create_city();
    KDTree_t blocks_tree = get_blocks_tree(city);
    KDTree_t vertex_tree = get_vertex_tree(city);
    Graph_t street_graph = get_street_graph(city);
    Vertex_t vertex = NULL;
    Edge_t edge = NULL;


    while(fscanf(geoFile, "%s", aux)!=EOF){
        if((strcmp(aux,"q"))==0) {
            // criar e armazenar quadra
            fscanf(geoFile, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            block = create_block(cep, x, y, w, h, sw, cstrk, cfill);
            point[0] = x; point[1] = y;
            insert_kd(blocks_tree, block, point);
        }
        if((strcmp(aux, "cq"))==0){
            // atualizar os valores de cores e expessura
            fscanf(geoFile, "%s %s %s", sw, cfill, cstrk);
        }
    }
    open_svg(geoSVGFile);
    print_tree(get_kd_root(blocks_tree), geoSVGFile, print_block);
    if(viaFile){
        char id[200], ldir[200], lesq[200], name[200], i[200], j[200];
        double cmp, vm, point[2];
        x = 0, y = 0;
        while(fscanf(viaFile, "%s", aux)!=EOF){
            if((strcmp(aux, "v"))==0){
                fscanf(viaFile, "%s %lf %lf", id, &x, &y);
                vertex = create_vertex(id, x, y);
                add_graph_vertex(street_graph, vertex);
                point[0] = x;
                point[1] = y;
                insert_kd(vertex_tree, vertex, point);
                // criar e armazenar o vertice;
            }
            if((strcmp(aux, "e"))==0){
                fscanf(viaFile, "%s %s %s %s %lf %lf %s", i, j, ldir, lesq, &cmp, &vm, name);
                edge = create_edge(name, i, j, ldir, lesq, cmp, vm);
                add_graph_edge(street_graph, edge);
            }
        }
        print_graph(get_street_graph(city), geoSVGFile);
    }
    close_svg(geoSVGFile);

    if(qryFile){
        qry_treat(city, qryFile, qrySVGFile, qryTXTFile);
        close_svg(qrySVGFile);
        if(viaFile){
            print_graph(get_street_graph(city), qrySVGFile);
        }
    }


    delete_city(city);
}
