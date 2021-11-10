#include "city.h"
#include "graph.h"
#include "kdtree.h"
#include <stdlib.h>

typedef struct City {
    KDTree_t blocks_tree;
    // Graph_t street_graph;
}City;

City_t create_city(){
    City *city = (City*) malloc(sizeof(City));
    city->blocks_tree = create_kd_tree();
    return city;
}

void insert_city_blocks_table(City_t  _city, KDTree_t _blocks_tree){
    City *city = (City*) _city;
    city->blocks_tree = _blocks_tree;
}

KDTree_t get_blocks_tree(City_t _city){
    City *city = (City*) _city;
    return city->blocks_tree;
}


void delete_city(City_t _city){
    City *city = (City*) _city;
    delete_kd(city->blocks_tree);
    free(_city);
}

