#ifndef QRY_FUNCTIONS_H_
#define QRY_FUNCTIONS_H_
#include "city.h"


Point_t arroba_o_int(City_t _city, char *cep, char face, int num, FILE *svgFile);

void catac(City_t _city, double x, double y, double w, double h, FILE *qrySVGFile, FILE *qryTXTFile);

Graph_t rv(City_t _city, double x, double y, double w, double h, double f);

#endif
