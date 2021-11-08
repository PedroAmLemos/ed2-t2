#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef void *List_t;

typedef void *Info_t;

typedef void *Node_t;

/*
 * Cria e retorna uma structList vazia;
 */
List_t create_list();

/*
 * Cria um structNode da lista com a info passada e armazena na lista;
 */
void insert_list(List_t _list, Info_t _info);

/*
 * Recebe uma lista, um node para remover e uma função de remoção que será aplicada na info do node;
 */
void remove_list_node(List_t list_, Node_t node_, void (*remove)(void*));

/*
 * Recebe a lista e uma função de remoção que será aplicada a info de cada node, remove todos os nodes da lista;
 */
void remove_list(List_t _list, void(*remove)(void*));

/*
 * Recebe a lista e retorna o primeiro node da lista;
 */
Node_t get_list_first(List_t list_);

/*
 * Recebe um node e retorna o próximo node da lista;
 */
Node_t get_list_next(Node_t node_);

/*
 * Retorna a info armazenada no node passado;
 */
Info_t get_list_info(Node_t node_);

/*
 * Recebe uma lista e retorna o tamanho dela;
 */
int get_list_size(List_t _list);

/*
 * Recebe uma lista de quadras e armazena os ceps, das que estiverem na área passada, na lista storage.
 * Pré: dois ponteiros void* para listas e uma área representada pelo ponto x, y, a largura e altura w, h.
 * Pós:
 */
void get_points_inside(List_t _list, List_t storage, double x, double y, double w, double h);


#endif // LINKED_LIST_H_
