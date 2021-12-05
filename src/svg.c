#include <stdio.h>
#include "edge.h"
#include "linked_list.h"
#include "svg.h"
#include "vertex.h"

void open_svg(FILE *svgFile){
    fprintf(svgFile, "<!-- Pedro Antonio Messias Lemos -->\n");
    fprintf(svgFile, "<svg version=\"1.1\" baseProfile=\"full\" width=\"15000\" height=\"15000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void close_svg(FILE *svgFile) {
    fprintf(svgFile, "</svg>");
}

void print_tree(KDTreeNode_t _node, FILE *svgFile, void(*print)(void*, FILE*)){
    if(_node == NULL) {
        return;
    }
    print_tree(get_kd_left(_node), svgFile, print);
    print_tree(get_kd_right(_node), svgFile, print);
    print(get_kd_node_info(_node), svgFile);
}

void print_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile){
    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" opacity=\"1\"/>\n",
            x1, y1, x2, y2, stroke);
}

void print_thick_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile){
    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" opacity=\"1\" stroke-width=\"6px\"/>\n",
            x1, y1, x2, y2, stroke);
}

void print_thicker_line(double x1, double y1, double x2, double y2, char stroke[], FILE *svgFile){
    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" opacity=\"1\" stroke-width=\"8px\"/>\n",
            x1, y1, x2, y2, stroke);
}

void print_text(double x, double y, char text[], FILE *svgFile){
   fprintf(svgFile, "\t<text x=\"%.2f\" y=\"%.2f\" font-size=\"2px\">%s</text>\n", x, y, text);
}

void print_circle(double cx, double cy, double r, char stroke[], char fill[], char sw[], FILE *svgFile){
    fprintf(svgFile, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" opacity=\"0.6\"/>\n", cx, cy, r, stroke, fill, sw);
}

void print_rectangle_dashed(double x, double y, double w, double h, FILE *svgFile){
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" opacity=\"1\" fill=\"none\" stroke=\"red\" stroke-width=\"10px\" stroke-dasharray=\"10\"/>\n", x, y, w, h);
}

void print_rectangle(double x, double y, double w, double h, char *fill, char *stroke, FILE *svgFile){
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" opacity=\"0.8\" fill=\"%s\" stroke=\"%s\" stroke-width=\"3px\" />\n", x, y, w, h, fill, stroke);
}

void print_vertex(Vertex_t _vertex, char* vertex_color, FILE* svg_file){
    fprintf(svg_file, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke=\"%s\" fill=\"black\" stroke-width=\"0.5\" />\n", get_vertex_x(_vertex), get_vertex_y(_vertex), vertex_color);
    print_text(get_vertex_x(_vertex), get_vertex_y(_vertex), get_vertex_name(_vertex), svg_file);
    //fprintf(svg_file, "\n\t<text x=\"%f\" y=\"%f\" text-anchor=\"middle\" font-size=\"0.13em\">%s</text>\n", get_vertex_x(_vertex), get_vertex_y(_vertex), get_vertex_name(_vertex));
}
void print_thick_vertex(Vertex_t _vertex, FILE* svg_file){
    fprintf(svg_file, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke=\"black\" fill=\"red\" stroke-width=\"0.5\" />\n", get_vertex_x(_vertex), get_vertex_y(_vertex));
}

void print_graph(Graph_t _graph, FILE *svgFile){
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    Vertex_t ending_vertex = NULL;
    List_t edge_list = NULL;
    Edge_t edge = NULL;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        vertex = get_graph_vertex(adj_list);
        edge_list = get_graph_edges(adj_list);
        print_vertex(vertex, "black", svgFile);
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            edge = get_list_info(edge_node);
            
            ending_vertex = get_graph_adj_list_vertex(_graph, get_edge_end_vertex_name(edge));
            print_line(get_vertex_x(vertex), get_vertex_y(vertex), get_vertex_x(ending_vertex), get_vertex_y(ending_vertex), "black", svgFile);
        }
    }
}

void print_graph_agm(Graph_t _graph, FILE *svgFile){
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    Vertex_t ending_vertex = NULL;
    List_t edge_list = NULL;
    Edge_t edge = NULL;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        adj_list = get_list_info(node);
        vertex = get_graph_vertex(adj_list);
        edge_list = get_graph_edges(adj_list);
        for(ListNode_t edge_node = get_list_first(edge_list); edge_node != NULL; edge_node = get_list_next(edge_node)){
            edge = get_list_info(edge_node);
            ending_vertex = get_graph_adj_list_vertex(_graph, get_edge_end_vertex_name(edge));
            print_thicker_line(get_vertex_x(vertex), get_vertex_y(vertex), get_vertex_x(ending_vertex), get_vertex_y(ending_vertex), "blue", svgFile);
        }
    }

}
void print_dijkstra_graph(Graph_t _graph, char *color, FILE *svgFile, int flag){
    AdjList_t adj_list = NULL;
    Vertex_t vertex = NULL;
    Vertex_t ending_vertex = NULL;

    int index = 0;
    for(ListNode_t node = get_list_first(_graph); node != NULL; node = get_list_next(node)){
        index++;
        if(index == get_list_size(_graph)){
            break;
        }
        adj_list = get_list_info(node);
        vertex = get_graph_vertex(adj_list);
        ending_vertex = get_graph_vertex(get_list_info(get_list_next(node)));
        if(flag)
            print_thicker_line(get_vertex_x(vertex)+2, get_vertex_y(vertex)+2, get_vertex_x(ending_vertex)+2, get_vertex_y(ending_vertex)+2, color, svgFile);
        else
            print_thicker_line(get_vertex_x(vertex), get_vertex_y(vertex), get_vertex_x(ending_vertex), get_vertex_y(ending_vertex), color, svgFile);
    }
    
}
