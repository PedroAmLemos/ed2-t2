#include <stdio.h>
#include <string.h>
#include "treatment.h"


void main_treatment(FILE *geoFile, FILE *qryFile, FILE *viaFile, FILE *geoSVGFile, FILE *geoTXTFile, FILE *qrySVGFile, FILE *qryTXTFile){
    double x = 0, y = 0, w = 0, h = 0; 
    char aux[5], cep[200], cfill[200], cstrk[200], sw[200];
    while(fscanf(geoFile, "%s", aux)!=EOF){
        if((strcmp(aux,"q"))==0) {
            fscanf(geoFile, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            // criar e armazenar quadra
        }
        if((strcmp(aux, "cq"))==0){
            // atualizar os valores de cores e expessura
            fscanf(geoFile, "%s %s %s", sw, cfill, cstrk);
        }
    }


    int nv;
    char id[200], ldir[200], lesq[200], cmp[200], vm[200], nome[200];
    double i = 0, j = 0;
    x = 0, y = 0;
    fscanf(viaFile, "%s", aux);
    if(strcmp(aux, "nv")==0) {
        fscanf(viaFile, "%d", &nv);
    }else{
        nv = 50000;
        rewind(viaFile);
    }

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
