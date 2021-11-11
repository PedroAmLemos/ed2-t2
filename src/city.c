#include "city.h"
#include <stdlib.h>

typedef struct City {
    KDTree_t blocks_tree;
    KDTree_t vertex_tree;
    Graph_t street_graph;
}City;

City_t create_city(){
    City *city = (City*) malloc(sizeof(City));
    city->blocks_tree = create_kd_tree();
    city->street_graph = create_graph();
    city->vertex_tree = create_kd_tree();
    return city;
}

void insert_city_blocks_tree(City_t  _city, KDTree_t _blocks_tree){
    City *city = (City*) _city;
    city->blocks_tree = _blocks_tree;
}

void insert_city_street_graph(City_t _city, Graph_t _street_graph){
    City *city = (City*) _city;
    city->street_graph = _street_graph;

}

void insert_city_vertex_tree(City_t _city, KDTree_t _vertex_tree){
    City *city = (City*) _city;
    city->vertex_tree = _vertex_tree;
}

Graph_t get_street_graph(City_t _city){
    City *city = (City*) _city;
    return city->street_graph;

}

KDTree_t get_blocks_tree(City_t _city){
    City *city = (City*) _city;
    return city->blocks_tree;
}

KDTree_t get_vertex_tree(City_t _city){
    City *city = (City*) _city;
    return city->vertex_tree;
}


void delete_city(City_t _city){
    City *city = (City*) _city;
    delete_full_graph(city->street_graph);
    delete_kd(city->blocks_tree, 1);
    delete_kd(city->vertex_tree, 0);
    free(_city);
}

