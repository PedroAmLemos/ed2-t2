#ifndef QRY_FUNCTIONS_H_
#define QRY_FUNCTIONS_H_
#include "city.h"


Point_t arroba_o_int(City_t _city, char *cep, char face, int num, FILE *svgFile);

void catac(City_t _city, double x, double y, double w, double h, FILE *qrySVGFile, FILE *qryTXTFile);

void rv(City_t _city, double x, double y, double w, double h, double f, FILE *qrySVGFile, FILE* qryTXTFile);

void cx(City_t city, double limiar, FILE *qrySVGFile, FILE *qryTXTFile);

#endif
