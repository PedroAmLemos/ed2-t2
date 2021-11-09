#include <stdio.h>
#include <string.h>
#include "svg.h"
#include "treatment.h"
#include "kdtree.h"
#include "block.h"


void main_treatment(FILE *geoFile, FILE *qryFile, FILE *viaFile, FILE *geoSVGFile, FILE *qrySVGFile, FILE *qryTXTFile){
    double x = 0, y = 0, w = 0, h = 0, point[2]; 
    char aux[5], cep[200], cfill[200], cstrk[200], sw[200];
    Block_t block;
    KDTree_t blocks_tree = create_kd_tree();


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
    close_svg(geoSVGFile);


    if(viaFile){
        char id[200], ldir[200], lesq[200], cmp[200], vm[200], nome[200];
        double i = 0, j = 0;
        x = 0, y = 0;
        while(fscanf(viaFile, "%s", aux)!=EOF){
            if((strcmp(aux, "v"))==0){
                fscanf(viaFile, "%s %lf %lf", id, &x, &y);
                // criar e armazenar o vertice;
            }
            if((strcmp(aux, "e"))==0){
                fscanf(viaFile, "%lf %lf %s %s %s %s %s", &i, &j, ldir, lesq, cmp, vm, nome);
                // criar e armazenar a aresta

            }
        }
    }



    delete_kd(blocks_tree);
}
