#include "block.h"
#include <string.h>
#include <stdlib.h>

typedef struct Block{
    char cep[200];
    double point[2];
    double width;
    double height;
    char sw[25];
    char stroke[25];
    char fill[25];
}Block;

Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]){
    Block *block = (Block*) malloc(sizeof(Block));
    strcpy(block->cep, cep);
    strcpy(block->sw, sw);
    strcpy(block->stroke, stroke);
    strcpy(block->fill, fill);
    block->width = width;
    block->height = height;
    block->point[0] =x;
    block->point[1] =y;

    return block;
}

char *get_block_cep(Block_t block_) {
    Block *block = (Block*) block_;
    return block->cep;
}

double get_block_x(Block_t block_) {
    Block *block = (Block*) block_;
    return block->point[0];
}

double get_block_y(Block_t block_) {
    Block *block = (Block*) block_;
    return block->point[1];
}

double *get_block_point(Block_t _block){
    Block *block = (Block*) _block;
    return block->point;
}

void print_block(Block_t block_, FILE *svgFile) {
    Block *block = (Block*) block_;
    if(block == NULL){
        return;
    }
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" opacity=\"0.8\" stroke=\"%s\" stroke-width=\"%s\"/>\n",
            block->point[0], block->point[1], block->width, block->height, block->fill, block->stroke, block->sw);
}
// void remove_block(HashTable_t _hashTable, AvlTree_t _tree, void(*remove)(void*, void*, void*, int), void *parameter){
//     remove(_hashTable, _tree, parameter, 1);
// }

double get_block_width(Block_t _block){
    Block *block = (Block*) _block;
    return block->width;
}

double get_block_height(Block_t _block){
    Block *block = (Block*) _block;
    return block->height;
}

char *get_block_sw(Block_t _block){
    Block *block = (Block*) _block;
    return block->sw;
}

char *get_block_stroke(Block_t _block){
    Block *block = (Block*) _block;
    return block->stroke;
}

char *get_block_fill(Block_t _block) {
    Block *block = (Block *) _block;
    return block->fill;
}

void print_block_txt(Block_t _block, FILE *qryTXTFile){
    Block *block = (Block *) _block;
    fprintf(qryTXTFile, "cep: %s\nponto: x = %.2lf, y = %.2lf\nlargura = %.2lf, altura = %.2lf\nespessura da borda: "
                        "%s, cor de preenchimento: %s, cor da borda: %s\n\n", block->cep, block->point[0], block->point[1], block->width,
                        block->height, block->sw, block->fill, block->stroke);

}

int is_block_inside_rect(Block_t _block, double x2, double y2, double w2, double h2){
    Block *block = (Block *) _block;
    double x1, y1, w1, h1;
    x1 = block->point[0];
    y1 = block->point[1];
    w1 = block->width;
    h1 = block->height;
    return x1 >= x2 && y1 >= y2 && x1 + w1 <= x2 + w2 && y1 + h1 <= y2 + h2;
}

void print_catac_block(Block_t _block, FILE *svgFile){
    Block *block = (Block*) _block;
    if(block == NULL){
        return;
    }
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"#AB37C8\" opacity=\"0.5\" stroke=\"#AA0044\" stroke-width=\"%s\"/>\n",
            block->point[0], block->point[1], block->width, block->height, block->sw);
}

