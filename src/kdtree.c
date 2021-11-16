#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "kdtree.h"
#include "block.h"

typedef struct KDTreeNode{
    KDTreeInfo_t info;
    // 0 para x e 1 para y
    int cd;
    double key[2];
    struct KDTreeNode *left;
    struct KDTreeNode *right;
}KDTreeNode;

typedef struct KDTree {
    KDTreeNode *root;
    int size;
}KDTree;

void insert_right(KDTreeNode *node, ListInfo_t info, double key[2]);
void insert_left(KDTreeNode_t node, ListInfo_t info, double key[2]);

KDTree_t create_kd_tree(){
    KDTree *new = (KDTree *) malloc(sizeof(KDTree));

    new->root = NULL;
    new->size = 0;

    return new;
}

void insert_right(KDTreeNode *node, ListInfo_t info, double key[2]){
    KDTreeNode *aux = (KDTreeNode *) node;

    if(aux->right == NULL){
        KDTreeNode *new = (KDTreeNode *) malloc(sizeof(KDTreeNode));

        new->info = info;
        new->key[0] = key[0];
        new->key[1] = key[1];
        new->left = NULL;
        new->right = NULL;
        new->cd = aux->cd == 0 ? 1 : 0;
        aux->right = new;


    }else{

        if(aux->right->key[aux->right->cd] > key[aux->right->cd]){
            insert_left(aux->right, info, key);

        }else{
            insert_right(aux->right, info, key);
        }

    }
}

void insert_left(KDTreeNode_t node, ListInfo_t info, double key[2]){
    KDTreeNode *aux = (KDTreeNode *) node;

    if(aux->left == NULL){
        KDTreeNode *new = (KDTreeNode *) malloc(sizeof(KDTreeNode));

        new->info = info;
        new->key[0] = key[0];
        new->key[1] = key[1];
        new->left = NULL;
        new->right = NULL;
        new->cd = aux->cd == 0 ? 1 : 0;
        aux->left = new;


    }else{
        if(aux->left->key[aux->left->cd] > key[aux->left->cd]){
            insert_left(aux->left, info, key);

        }else{
            insert_right(aux->left, info, key);
        }

    }

}

void insert_kd(KDTree_t _tree, ListInfo_t info, double key[2]){
    KDTree *tree = (KDTree *) _tree;

    if(tree->root == NULL){
        KDTreeNode *new = (KDTreeNode *) malloc(sizeof(KDTreeNode));

        new->info = info;
        new->key[0] = key[0];
        new->key[1] = key[1];
        new->left = NULL;
        new->right = NULL;
        new->cd = 0;
        tree->root = new;

    }else{
        if(tree->root->key[tree->root->cd] > key[tree->root->cd]){
            insert_left(tree->root, info, key);

        }else{
            insert_right(tree->root, info, key);
        }
    }

    tree->size++;
}

KDTreeNode_t min_node(KDTreeNode_t x, KDTreeNode_t y, KDTreeNode_t z, int d){
    KDTreeNode *res = (KDTreeNode*) x;
    KDTreeNode *aux2  = (KDTreeNode*) y;
    KDTreeNode *aux  = (KDTreeNode*) z;
    if(aux2 != NULL && aux2->key[d] < res->key[d]){
        res = y;
    }
    if(aux != NULL && aux->key[d] < res->key[d]){
        res = z;
    }
    return res;
}

KDTreeNode_t find_min_kd(KDTreeNode_t tree, int d){
    KDTreeNode* root = (KDTreeNode*) tree;

    if(root == NULL){
        return root;
    }

    int cd = root->cd;

    if(cd == d){
        if(root->left == NULL){
            return root;
        }
        return find_min_kd(root->left, d);
    }
    return min_node(root, find_min_kd(root->left, d), find_min_kd(root->right, d), d);
}

KDTreeNode_t remove_node_aux(KDTreeNode_t node, double key[2]){
    KDTreeNode *node_aux = (KDTreeNode *) node;

    if(node_aux == NULL){
        return NULL;
    }

    if(key[0] == node_aux->key[0] && key[1] == node_aux->key[1]){
        if(node_aux->right != NULL){
            KDTreeNode *aux = (KDTreeNode *) find_min_kd(node_aux->right, node_aux->cd);
            node_aux->key[1] = aux->key[1];
            node_aux->key[0] = aux->key[0];
            node_aux->info = aux->info;
            node_aux->right = remove_node_aux(node_aux->right, node_aux->key);

        }else if(node_aux->left != NULL){
            KDTreeNode *aux = (KDTreeNode *) find_min_kd(node_aux->left, node_aux->cd);
            node_aux->key[1] = aux->key[1];
            node_aux->key[0] = aux->key[0];
            node_aux->info = aux->info;
            node_aux->right = remove_node_aux(node_aux->left, node_aux->key);
            node_aux->left = NULL;
        }else{
            free(node_aux);
            return NULL;
        }

    } else if (key[node_aux->cd] < node_aux->key[node_aux->cd]){
        node_aux->left = remove_node_aux(node_aux->left, key);

    }else{
        node_aux->right = remove_node_aux(node_aux->right, key);

    }

    return node_aux;
}

void remove_kd_node(KDTree_t tree, double key[2]){
    KDTree *tree_aux = (KDTree *) tree;

    if(tree_aux->size > 0){
        tree_aux->root = remove_node_aux(tree_aux->root, key);
        tree_aux->size--;
    }

}

void remove_kd_all(KDTreeNode_t _node, int flag){
    KDTreeNode *node = (KDTreeNode *) _node;

    if(node->left != NULL){
        remove_kd_all(node->left, flag);
    }
    if(node->right != NULL){
        remove_kd_all(node->right, flag);
    }
    if(flag){
        free(node->info);

    }
    free(node);
}

void delete_kd(KDTree_t _tree, int flag){
    KDTree *tree = (KDTree *) _tree;

    if(tree->root != NULL){
        remove_kd_all(tree->root, flag);
    }
    free(tree);
}

KDTreeNode_t find_node(KDTreeNode_t _node, double key[2]){
    KDTreeNode *node = (KDTreeNode *) _node;

    if(node == NULL || (node->key[1] == key[1] && node->key[0] == key[0])){
        return node;
    }

    if(node->key[node->cd] > key[node->cd]){
        return find_node(node->left, key);
    }else{
        return find_node(node->right, key);
    }
}

ListInfo_t get_kd_node_info_from_key(KDTree_t _tree, double key[2]){
    KDTree *tree = (KDTree *) _tree;

    KDTreeNode *node = find_node(tree->root, key);

    if(node != NULL){
        return node->info;
    }

    return NULL;
}

ListInfo_t get_kd_node_info(KDTreeNode_t _node){
    KDTreeNode *node = (KDTreeNode *) _node;

    return node->info;
}

KDTreeNode_t get_kd_left(KDTreeNode_t _node){
    KDTreeNode *node = (KDTreeNode *) _node;

    return node->left;
}

KDTreeNode_t get_kd_right(KDTreeNode_t _node){
    KDTreeNode *node = (KDTreeNode *) _node;

    return node->right;
}

KDTreeNode_t get_kd_root(KDTree_t _tree){
    KDTree *tree = (KDTree *) _tree;

    return tree->root;
}

int get_kd_size(KDTree_t _tree){
    KDTree *tree = (KDTree *) _tree;

    return tree->size;
}

int get_kd_dim(KDTreeNode_t _node){
    KDTreeNode *node = (KDTreeNode *) _node;

    return node->cd;
}

void get_points_inside_aux(List_t _list, KDTreeNode_t _root, double x, double y, double w, double h){
    KDTreeNode *root = (KDTreeNode *) _root;

    if(_root == NULL){
        return;
    }

    if(root->key[0] >= x && root->key[0] <= (x + w)){
        if(root->key[1] >= y && root->key[1] <= (y + h)){
            double *aux = malloc(2*(sizeof(double)));
            aux[0] = root->key[0];
            aux[1] = root->key[1];
            insert_list(_list, aux);
        }
    }

    double key_aux[2] = {x, y};
    double key_aux2[2] = {x+w, y+h};

    if(key_aux2[root->cd] >= root->key[root->cd]){
        get_points_inside_aux(_list, root->right, x, y, w, h);
    }
    if(key_aux[root->cd] <= root->key[root->cd]){
        get_points_inside_aux(_list, root->left, x, y, w, h);
    }
}

List_t get_points_inside_kd(KDTree_t _tree, double x, double y, double w, double h){
    KDTree *tree = (KDTree *) _tree;

    List_t list = create_list();
    get_points_inside_aux(list, tree->root, x, y, w, h);

    return list;
}

double* get_kd_min(KDTreeNode_t _root){
    KDTreeNode *root = (KDTreeNode *) _root;

    if(_root == NULL){
        return NULL;
    }

    if(root->left != NULL){
        return get_kd_min(root->left);
    }

    return root->key;
}

double* get_kd_max(KDTreeNode_t _root){
    KDTreeNode *root = (KDTreeNode *) _root;

    if(_root == NULL){
        return NULL;
    }

    if(root->right != NULL){
        return get_kd_max(root->right);
    }

    return root->key;
}


void get_info_inside_aux(List_t _list, KDTreeNode_t _root, double x, double y, double w, double h){
    KDTreeNode *root = (KDTreeNode *) _root;

    if(_root == NULL){
        return;
    }

    if(root->key[0] >= x && root->key[0] <= (x + w)){
        if(root->key[1] >= y && root->key[1] <= (y + h)){
            insert_list(_list, get_kd_node_info(root));
        }
    }

    double key_aux[2] = {x, y};
    double key_aux2[2] = {x+w, y+h};

    if(key_aux2[root->cd] >= root->key[root->cd]){
        get_info_inside_aux(_list, root->right, x, y, w, h);
    }
    if(key_aux[root->cd] <= root->key[root->cd]){
        get_info_inside_aux(_list, root->left, x, y, w, h);
    }
}

List_t get_info_inside_kd(KDTree_t _tree, double x, double y, double w, double h){
    KDTree *tree = (KDTree *) _tree;

    List_t list = create_list();
    get_info_inside_aux(list, tree->root, x, y, w, h);

    return list;
}

void get_block_from_cep(KDTreeNode_t _root, char *cep, Block_t *result){
    if(_root == NULL){
        return;
    }
    KDTreeNode *node = (KDTreeNode*) _root;
    KDTreeInfo_t block = get_kd_node_info(node);
    char *block_cep = get_block_cep(block);
    if(strcmp(cep, block_cep) == 0){
        *result = block;
        return;
    }
    get_block_from_cep(node->right, cep, result);
    get_block_from_cep(node->left, cep, result);
}

