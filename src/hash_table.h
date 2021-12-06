#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "linked_list.h"

typedef void *HashTable_t;
typedef void *Item_t;
typedef void *Info_t;
typedef void *Node_t;

/*
 * Desaloca memória alocada para um item armazenado na hash table.
 * Pré: Recebe um ponteiro do tipo void* para um item que será desalocado.
 * Pós:
 */
void delete_item(void *item_);

/*
 * Aloca memória e cria uma hash table, inicializa as listas com NULL.
 * Pré: um inteiro contendo o tamanho da lista.
 * Pós: um ponteiro do tipo void* para a hash table criada.
 */
HashTable_t create_hash_table(int size);

/*
 * Insere uma informação na hash table.
 * Pré: um ponteiro do tipo void* para a hash table, uma chave para inserção e um ponteiro do tipo void* com a
 * informação.
 * Pós:
 */
void insert_hash(HashTable_t _hashTable, char *key, Info_t _info);

/*
 * Desaloca a memória alocada de uma hash table.
 * Pré: ponteiro void* para a tabela e uma flag do tipo inteiro sendo 0 para desalocar a info e 1 para não desalocar.
 * Pós:
 */
void delete_hash_table(HashTable_t _hashTable, int flag);

/*
 * Remove um item de uma hash table.
 * Pré: ponteiro void* para a tabela, uma chave de busca e uma flag do tipo inteiro sendo 0 para desalocar a
 * info e 1 para não desalocar.
 * Pós:
 */
void remove_item(HashTable_t _hashTable, char key[], int flag);

/*
 * Função hash para a inserção na hash table.
 * Pré: uma chave e o tamanho da tabela.
 * Pós: um unsigned long int da posição na tabela para inserção.
 */
unsigned long int hash_function(char *key, int size);

// Altera a info deu elemento da hash table 
void change_value(HashTable_t _hashTable, char *key, Info_t new);

/*
 * Getters: Retorna o atributo do título da função.
 * Pré: Objeto.
 * Pós: Atributo especificado.
 */
List_t get_table_list(HashTable_t _hashTable, char *key);
Info_t get_info_from_key(HashTable_t _hashTable, char *key);
List_t get_index_list(HashTable_t _hashTable, int index);
Item_t get_item(HashTable_t _hashtable, char key[]);
int get_table_size(HashTable_t *_hashTable);
void *get_item_info(Item_t _item);
List_t *get_table(HashTable_t _hashTable);


#endif // HASH_TABLE_H_
