#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linked_list.h"
#include "hash_table.h"

typedef struct{
    int size;
    List_t *table;
}Hash;

typedef struct{
    char key[25];
    Info_t info;
}HashTableItem;

void delete_item(void *item_){
    HashTableItem *item = (HashTableItem*) item_;
    free(item->info);
    free(item);
}

HashTable_t create_hash_table(int size){
    Hash *hashTable = (Hash*) malloc(sizeof(Hash));
    int i;

    hashTable->size = size;
    hashTable->table = (List_t*)malloc(sizeof(List_t)*size);

    for (i = 0; i < size; i++) {
        hashTable->table[i] = create_list();
    }

    return hashTable;
}

unsigned long int hash_function(char *_key, int size){
    unsigned int hash = 5381;
    unsigned char *key = (unsigned char*) _key;
    int c;
    while ((c = *key++)) {
        if (isupper(c)) {
            c = c + 32;
        }
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

void insert_hash(HashTable_t _hashTable, char key[], Info_t _info){
    Hash *hashTable = (Hash*) _hashTable;
    unsigned long int hash = hash_function(key, hashTable->size);

    HashTableItem *info_s = (HashTableItem*) malloc(sizeof(HashTableItem));
    info_s->info = _info;
    strcpy(info_s->key, key);

    insert_list(hashTable->table[hash], info_s);
}

int get_table_size(HashTable_t *_hashTable){
    Hash *hashTable = (Hash*)_hashTable;
    return hashTable->size;
}

List_t get_table_list(HashTable_t _hashTable, char *key){
    Hash *hashTable = (Hash*)_hashTable;
    unsigned long int hashKey = hash_function(key, hashTable->size);
    if((int) hashKey >= hashTable->size){
        return NULL;
    }
    return hashTable->table[hashKey];
}

Item_t get_item(HashTable_t _hashtable, char key[]) {
    Hash *hashTable = (Hash*) _hashtable;
    unsigned long int hashKey = hash_function(key, hashTable->size);
    for(Node_t aux = get_list_first(hashTable->table[hashKey]); aux != NULL; aux = get_list_next(aux)){
        HashTableItem *item = (HashTableItem*) get_list_info(aux);
        if(strcmp(item->key, key) == 0) {
            return item->info;
        }
    }
    return NULL;
}

void remove_item(HashTable_t _hashTable, char key[], int flag){
    Hash *hashTable = (Hash*) _hashTable;
    unsigned long int hashKey = hash_function(key, hashTable->size);
    void (*carlos[2])(void*) = {free, delete_item};

    for(Node_t aux = get_list_first(hashTable->table[hashKey]); aux != NULL; aux = get_list_next(aux)){
        HashTableItem *item = (HashTableItem*) get_list_info(aux);
        if(strcmp(item->key, key) == 0) {
            remove_list_node(hashTable->table[hashKey], aux, carlos[flag]);
            return;
        }
    }
}

void delete_hash_table(HashTable_t _hashTable, int flag){
    if(_hashTable == NULL){
        return;
    }
    void (*carlos[2])(void*) = {free, delete_item};
    Hash *hashTable = (Hash*)_hashTable;
    int i;
    List_t *lists = hashTable->table;
    for (i = 0; i < hashTable->size; i++) {
        remove_list(lists[i], carlos[flag]);
    }
    free(lists);
    free(hashTable);
}

List_t *get_table(HashTable_t _hashTable){
    Hash *hashTable = (Hash*)_hashTable;
    return hashTable->table;
}

void *get_item_info(Item_t _item){
    HashTableItem *item = (HashTableItem *) _item;
    return item->info;
}


char *get_item_key(Item_t _item){
    HashTableItem *item = (HashTableItem*) _item;
    return item->key;
}

Info_t get_info_from_key(HashTable_t _hashTable, char *key){
    Hash *hashTable = (Hash*)_hashTable;
    List_t keyList = get_table_list(hashTable, key);
    Item_t item;
    if (keyList == NULL){
        return NULL;
    }
    for(Node_t node = get_list_first(keyList); node != NULL; node = get_list_next(node)){
        item = get_list_info(node);
        if(strcmp(get_item_key(item), key) == 0){
            return get_item_info(item);
        }
    }
    return NULL;

}

List_t get_index_list(HashTable_t _hashTable, int index){
    Hash *hashTable = (Hash*)_hashTable;
    if(hashTable->table[index] != NULL){
        return hashTable->table[index];
    }
    return NULL;
}
