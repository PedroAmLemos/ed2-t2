#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"

int main(int argc, char *argv[]){
    int i = 1;
    char *entryPath = NULL; // bed diretório de entrada, opcional
    char *outPath = NULL;   // bsd diretório de saida, obrigatório
    char *geo = NULL;       // arquivo de descrição, sob o diretório bed, obrigatório
    char *qry = NULL;       // arquivo de consultas, sob o diretório bed, obrigatório
    char *via = NULL;
    while (i < argc) {
        if (strcmp("-e", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -e\n");
                exit(1);
            }
            entryPath = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entryPath, argv[i]);
        } else if (strcmp("-f", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -f\n");
                exit(1);
            }
            geo = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(geo, argv[i]);
        } else if (strcmp("-o", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -o\n");
                exit(1);
            }
            outPath = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(outPath, argv[i]);
        } else if (strcmp("-q", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -q\n");
                exit(1);
            }
            qry = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(qry, argv[i]);
        } else if (strcmp("-via", argv[i]) == 0) {
            i++;
            if (argv[i] == NULL) {
                printf("Erro - Sem parâmetros em -via\n");
                exit(1);
            }
            via = malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(via, argv[i]);
        }
        i++;
    }
    read(entryPath, geo, qry, outPath, via);


    free(geo);
    free(outPath);
    if (entryPath){
        free(entryPath);
    }
    if(qry){
       free(qry);
    }
    if(via){
        free(via);
    }
    return 0;
}
