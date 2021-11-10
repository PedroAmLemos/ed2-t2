#include <string.h>
#include <stdio.h>
#include "qry.h"
#include "svg.h"
#include "block.h"
#include "qry_functions.h"
// #include "qry_functions.h"

void qry_treat(City_t city, FILE *qryFile, FILE *qrySVGFile, FILE *qryTXTFile){
    char aux[5];
    // cep[25], cpf[20], side, compl[25], id[50], dmptFilename[50];
    double x, y, w, h;

    open_svg(qrySVGFile);

    while(fscanf(qryFile, "%s", aux) != EOF){
        if(strcmp(aux, "catac") == 0){
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            fprintf(qryTXTFile, "catac\n");
            catac(city, x, y, w, h, qrySVGFile, qryTXTFile);
            fprintf(qryTXTFile, "\n\n");
        }
    }

    print_tree(get_kd_root(get_blocks_tree(city)), qrySVGFile, print_block);

    close_svg(qrySVGFile);
}
