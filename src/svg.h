#ifndef SVG_H_
#define SVG_H_
#include <stdio.h>
#include "graph.h"
#include "kdtree.h"

/*
 * Função que abre a tag svg em um arquivo passado.
 * Pré: ponteiro para o arquivo svg.
 * Pós:
 */
void open_svg(FILE *svgFile);

/*
 * Função que fecha a tag svg em um arquivo passado.
 * Pré: ponteiro para o arquivo svg.
 * Pós:
 */
void close_svg(FILE *svgFile);

/*
 * Função que imprime as informações de uma árvore em um arquivo passado.
 * Pré: ponteiro do tipo void* para a árvore, ponteiro para o arquivo svg e uma função que realizará a impressão.
 * Pós:
 */
void print_tree(KDTree_t tree_, FILE *svgFile, void(*print)(void*, FILE*));


/*
 * Imprime uma linha em um arquivo svg.
 * Pré: os valores para impressão da linha e o arquivo svg.
 * Pós:
 */
void print_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile);

/*
 * Imprime um texto em um arquivo svg.
 * Pré: os valores para a impressão do texto e o arquivo svg.
 * Pós:
 */
void print_text(double x, double y, char text[], FILE *svgFile);

/*
 * Imprime um círculo em um arquivo svg.
 * Pré: os valores para a impressão do círculo e o arquivo svg.
 * Pós:
 */
void print_circle(double cx, double cy, double r, char stroke[], char fill[], char sw[], FILE *svgFile);

/*
 * Imprime um retângulo tracejado.
 * Pré: recebe os valores para impressão e o arquivo svg.
 * Pós:
 */
void print_rectangle_dashed(double x, double y, double w, double h, FILE *svgFile);

/*
 * Imprime um retângulo.
 * Pré: recebe os valores para impressão e o arquivo svg.
 * Pós:
 */
void print_rectangle(double x, double y, double w, double h, char *fill, char *stroke, FILE *svgFile);

// Imprime um grafo passado em um svg
void print_graph(Graph_t _graph, FILE *svgFile);

// Imprime um vértice em um svg passado
void print_vertex(Vertex_t _vertex, char* vertex_color, FILE* svg_file);

// Imprime a árvore geradora minima em um svg passado
void print_graph_agm(Graph_t _graph, FILE *svgFile);

// Imprime um vertice grosso no svg
void print_thick_vertex(Vertex_t _vertex, FILE* svg_file);

// Imprime uma linha mais grossa no svg
void print_thicker_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile);

// Imprime uma linha grossa no svg
void print_thick_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile);

// Imprime um grafo de dijkstra no svg
void print_dijkstra_graph(Graph_t _graph, char *color, FILE *svgFile, int flag);

// Imprime uma linha pontilhada no svg
void print_dashed_line(double x1, double y1, double x2, double y2, char *stroke, FILE *svgFile);

// Imprime a animação do trajeto passado no svg
void print_animated_circle(double x1, double y1, List_t path,  FILE *svgFile, int flag);

#endif //SVG_H_
