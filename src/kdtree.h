#ifndef KD_TREE_H
#define KD_TREE_H

#include "linked_list.h"
#include "block.h"

typedef void* KDTree_t;
typedef void* KDTreeNode_t;
typedef void* KDTreeInfo_t;

// Cria uma árvore kd
KDTree_t create_kd_tree();

// Insere a info passad na árvore kd
void insert_kd(KDTree_t _tree, KDTreeInfo_t info, double key[2]);

// Deleta o node, com a chave passada, da árvore kd
void remove_kd_node(KDTree_t tree, double key[2]);

// Desaloca toda a árvore kd e suas infos
void delete_kd(KDTree_t _tree, int flag);

// Retorna info de um node passado
KDTreeInfo_t get_kd_node_info(KDTreeNode_t _node);

// Retorna a info do node com a chave passada
KDTreeInfo_t get_kd_node_info_from_key(KDTree_t _tree, double key[2]);

// Retorna o node à esquerda do node passado
KDTreeNode_t get_kd_left(KDTreeNode_t _node);

// Retorna o node a direta do node passado
KDTreeNode_t get_kd_right(KDTreeNode_t _node);

// Retorna o node raiz da árvore passada
KDTreeNode_t get_kd_root(KDTree_t _tree);

// Retorna o número de nodes na árvore
int get_kd_size(KDTree_t _tree);

// Retorna a profundidade do node passado
int get_kd_dim(KDTreeNode_t _node);

// Retorna uma lista com os nodes no retângulo passado
List_t get_points_inside_kd(KDTree_t _tree, double x, double y, double w, double h);

// Retorna o menor ponto na árvore
double* get_kd_min(KDTreeNode_t _root);

// Retorna o maior ponto na árvore
double* get_kd_max(KDTreeNode_t _root);

List_t get_info_inside_kd(KDTree_t _tree, double x, double y, double w, double h);

void get_block_from_cep(KDTreeNode_t _root, char *cep, Block_t *result);
#endif
