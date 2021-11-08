#ifndef BLOCK_H_
#define BLOCK_H_
#include <stdio.h>
typedef void *Block_t;

/*
 * Aloca memória e atribui valores para uma nova quadra.
 * Pré: recebe os atributos para criação da quadra.
 * Pós: ponteiro para a quadra criada.
 */
Block_t create_block(char cep[], double x, double y, double width, double height, char sw[], char stroke[], char fill[]);

/*
 * Função para impressão de uma quadra no arquivo svg.
 * Pré: recebe uma quadra e um arquivo svg para a impressão.
 * Pós:
 */
void print_block(Block_t block_, FILE *svgFile);

/*
 * Função responsável por remover uma quadra da hash table e da árvore.
 * Pré: ponteiro void* para a hash table, ponteiro void* para a arquivo, um function pointer para a função que irá
 * remover a quadra, um parametro do tipo void* que pode ser uma string (cep) ou um vetor[2] do tipo double (ponto)
 * Pós:
 */
// void remove_block(HashTable_t hashTable, AvlTree_t _tree, void(*remover)(void*, void*, void*, int), void *parameter);

/*
 * Imprime os dados de uma quadra em um arquivo txt
 * Pré: ponteiro void* para a quadra, ponteiro para um arquivo.
 * Pós:
 */
void print_block_txt(Block_t _block, FILE *qryTXTFile);

/*
 * Indica se uma quadra está dentro de uma área retangular.
 * Pré: ponteiro void* para a quadra, o ponto x, y do tipo double, a largura e a altura.
 * Pós: 1 caso esteja dentro e 0 caso contrário.
 */
int is_block_inside_rect(Block_t _block, double x, double y, double w, double h);

/*
 * Função para imprimir as quadras do comando catac no arquivo svg.
 * Pré: um ponteiro void* para uma quadra e um ponteiro para o arquivo svg.
 * Pós:
 */
void print_catac_block(Block_t _block, FILE *svgFile);

/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
 */
char *get_block_cep(Block_t block_);
double get_block_x(Block_t block_);
double get_block_y(Block_t block_);
double *get_block_point(Block_t _block);
double get_block_width(Block_t _block);
double get_block_height(Block_t _block);
char *get_block_sw(Block_t _block);
char *get_block_stroke(Block_t _block);
char *get_block_fill(Block_t _block);

#endif //BLOCK_H_
