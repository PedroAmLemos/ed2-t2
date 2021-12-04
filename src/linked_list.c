#include "linked_list.h"
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    ListInfo_t info;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct{
    int size;
    Node *first;
    Node *last;
}List;

List_t create_list(){
    List *list = (List*) malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

void insert_list(List_t _list, ListInfo_t _info){
    List *list = (List*) _list;
    Node *node  = (Node*) malloc(sizeof(Node));
    node->info  = _info;
    if(list->first==NULL){
        node->prev  = NULL;
        list->first = node;
    }else{
        list->last->next = node;
        node->prev = list->last;
    }
    node->next = NULL;
    list->last = node;
    list->size++;
}

void remove_list_node(List_t list_, ListNode_t node_, void (*remove)(void*)){
    List *list = (List*) list_;
    Node *node = (Node*) node_;

    if(node->prev == NULL){
        list->first = node->next;
    }else{
        node->prev->next = node->next;
    }
    if(node->next == NULL) {
        list->last = node->prev;
    }else{
        node->next->prev = node->prev;
    }

    if(remove != NULL) remove(get_list_info(node));
    free(node);
    list->size--;
}

void remove_list(List_t _list, void(*remove)(void*)){
    List *list = (List*) _list;
    Node *node = list->first;
    Node *aux;
    while (node != NULL) {
        aux = node;
        node = node->next;
        if(remove != NULL)
            remove(aux->info);
        free(aux);
    }
    free(list);
}

ListNode_t get_list_first(List_t list_){
    List *list = (List*) list_;
    return list->first;
}

ListNode_t get_list_last(List_t _list){
    List *list = (List*) _list;
    return list->last;
}

ListNode_t get_list_next(ListNode_t node_){
    Node *list = (Node*) node_;
    return list->next;
}
ListNode_t get_list_previous(ListNode_t node_){
    Node *list = (Node*) node_;
    return list->prev;
}

ListInfo_t get_list_info(ListNode_t node_){
    Node *list = (Node*) node_;

    return list->info;
}

int get_list_size(List_t _list){
    List *list = (List*) _list;
    return list->size;
}

ListNode_t get_list_index_node(List_t _list, int index){
    List *list = (List*) _list;
    int index_aux = 0;
    for(Node *node = list->first; node != NULL; node = node->next){
        if(index_aux == index){
            return node;
        }
        index_aux++;
    }
    return NULL;
}

void swap_list_info(ListNode_t _a, ListNode_t _b) {
    Node* a = (Node*) _a;
    Node* b = (Node*) _b;
    ListInfo_t aux;
    aux = a->info;
    a->info = b->info;
    b->info = aux;
}

int is_string_in_list(List_t _list, char *text){
    for(Node_t node = get_list_first(_list); node != NULL; node = get_list_next(node)){
        if(strcmp(get_list_info(node), text)==0){
            return 1;
        }
    }
    return 0;
}


List_t reverse_linked_list(List_t _list){
    List *reverse = create_list();
    for(Node_t node = get_list_last(_list); node != NULL; node = get_list_previous(node)){
        insert_list(reverse, get_list_info(node));
    }
    return reverse;
}

