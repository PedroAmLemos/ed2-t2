#ifndef CITY_H_
#define CITY_H_
#include "kdtree.h"
#include <stdio.h>

typedef void *City_t;

/*
 * Função responsável por criar uma struct cidade e inicializar as tabelas e a árvore necessários.
 * Pré: o número de pessoas.
 * Pós: um ponteiro do tipo void* para a cidade criada.
 */
City_t create_city();

/*
 * Função responsável por desalocar toda memória alocada para a cidade e os seus componentes.
 * Pré: um ponteiro do tipo void* para a cidade.
 * Pós:
 */
void delete_city(City_t _city);

/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
*/
void insert_city_blocks_table(City_t  _city, KDTree_t _blocks_tree);
KDTree_t get_blocks_tree(City_t _city);


#endif //CITY_H_

