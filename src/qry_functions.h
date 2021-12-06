#ifndef QRY_FUNCTIONS_H_
#define QRY_FUNCTIONS_H_
#include "city.h"


// Executa a função @o?
Point_t arroba_o_int(City_t _city, char *cep, char face, int num, FILE *svgFile, int flag);

// Executa a função catac
void catac(City_t _city, double x, double y, double w, double h, FILE *qrySVGFile, FILE *qryTXTFile);

// Executa a função rv
void rv(City_t _city, double x, double y, double w, double h, double f, FILE *qrySVGFile, FILE* qryTXTFile);

// Executa a função cx
void cx(City_t city, double limiar, FILE *qrySVGFile, FILE *qryTXTFile);

// Executa a função p?
void p_i(City_t _city, Point_t start_point, char *cep, char face, int num, char *cmc, char *cmr, FILE *svgFile, FILE *txtFile);

#endif
