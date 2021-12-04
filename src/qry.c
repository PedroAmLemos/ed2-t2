#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "graph.h"
#include "qry.h"
#include "svg.h"
#include "block.h"
#include "qry_functions.h"
#include "linked_list.h"
#include "vertex.h"

void qry_treat(City_t city, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile){
    char aux[5];
    double x, y, w, h, f, limiar;
    char cep[200], face;
    int num;
    Point_t o_point = NULL;
    open_svg(qrySVGFile);

    while(fscanf(qryFile, "%s", aux) != EOF){
        if(strcmp(aux, "@o?") == 0){
            fscanf(qryFile, "%s %s %d", cep, &face, &num);
            fprintf(qryTXTFile, "@o?\n\n");
            o_point = arroba_o_int(city, cep, face, num, qrySVGFile, 1);
        }
        if(strcmp(aux, "catac") == 0){
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            fprintf(qryTXTFile, "catac\n");
            catac(city, x, y, w, h, qrySVGFile, qryTXTFile);
            fprintf(qryTXTFile, "\n\n");
        }
        if(strcmp(aux, "rv") == 0){
            fscanf(qryFile, "%lf %lf %lf %lf %lf", &x, &y, &w, &h, &f);
            fprintf(qryTXTFile, "rv\n");
            rv(city, x, y, w, h, f, qrySVGFile, qryTXTFile);
        }
        if(strcmp(aux, "cx") == 0){
            fscanf(qryFile, "%lf", &limiar);
            fprintf(qryTXTFile, "cx\n");
            cx(city, limiar, qrySVGFile, qryTXTFile);
        }
        if(strcmp(aux, "p?") == 0){
            fscanf(qryFile, "%lf", &limiar);
            fscanf(qryFile, "%s %s %d", cep, &face, &num);
            p_i(city, o_point, cep, face, num, qrySVGFile, qryTXTFile);
        }
    }

    print_tree(get_kd_root(get_blocks_tree(city)), qrySVGFile, print_block);
    free(o_point);
}
