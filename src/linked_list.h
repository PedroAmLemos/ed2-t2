#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef void *List_t;

typedef void *ListInfo_t;

typedef void *ListNode_t;

/*
 * Cria e retorna uma structList vazia;
 */
List_t create_list();

/*
 * Cria um structNode da lista com a info passada e armazena na lista;
 */
void insert_list(List_t _list, ListInfo_t _info);

/*
 * Recebe uma lista, um node para remover e uma função de remoção que será aplicada na info do node;
 */
void remove_list_node(List_t list_, ListNode_t node_, void (*remove)(void*));

/*
 * Recebe a lista e uma função de remoção que será aplicada a info de cada node, remove todos os nodes da lista;
 */
void remove_list(List_t _list, void(*remove)(void*));

/*
 * Recebe a lista e retorna o primeiro node da lista;
 */
ListNode_t get_list_first(List_t list_);

ListNode_t get_list_last(List_t _list);

/*
 * Recebe um node e retorna o próximo node da lista;
 */
ListNode_t get_list_next(ListNode_t node_);

/*
 * Retorna a info armazenada no node passado;
 */
ListInfo_t get_list_info(ListNode_t node_);

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

// Retorna o node do index passado
ListNode_t get_list_index_node(List_t _list, int index);

// Troca as infos de dois nodes passados
void swap_list_info(ListNode_t _a, ListNode_t _b);

// Retorna se uma string está presente na lista
int is_string_in_list(List_t _list, char *text);

// Retorna uma lista com os nodes invertidos
List_t reverse_linked_list(List_t _list);
#endif // LINKED_LIST_H_
