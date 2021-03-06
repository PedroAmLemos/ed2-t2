#include <stdio.h>
#include "edge.h"
#include "linked_list.h"
#include "svg.h"
#include "vertex.h"

void open_svg(FILE *svgFile){
    fprintf(svgFile, "<!-- Pedro Antonio Messias Lemos -->\n");
    fprintf(svgFile, "<svg version=\"1.1\" baseProfile=\"full\" width=\"50000\" height=\"50000\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
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
    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" opacity=\"1\" stroke-width=\"12px\"/>\n",
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

void print_dashed_line(double x1, double y1, double x2, double y2, char *stroke, FILE *svgFile){
    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" opacity=\"1\" stroke-dasharray=\"10\"/>\n",
            x1, y1, x2, y2, stroke);
}

void print_rectangle(double x, double y, double w, double h, char *fill, char *stroke, FILE *svgFile){
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" opacity=\"0.8\" fill=\"%s\" stroke=\"%s\" stroke-width=\"3px\" />\n", x, y, w, h, fill, stroke);
}

void print_vertex(Vertex_t _vertex, char* vertex_color, FILE* svg_file){
    fprintf(svg_file, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke=\"%s\" fill=\"black\" stroke-width=\"0.5\" />\n", get_vertex_x(_vertex), get_vertex_y(_vertex), vertex_color);
    //print_text(get_vertex_x(_vertex), get_vertex_y(_vertex), get_vertex_name(_vertex), svg_file);
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
            print_thicker_line(get_vertex_x(vertex), get_vertex_y(vertex), get_vertex_x(ending_vertex), get_vertex_y(ending_vertex), "lightgreen", svgFile);
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
            print_thick_line(get_vertex_x(vertex)+4, get_vertex_y(vertex)+4, get_vertex_x(ending_vertex)+4, get_vertex_y(ending_vertex)+4, color, svgFile);
        else
            print_thick_line(get_vertex_x(vertex), get_vertex_y(vertex), get_vertex_x(ending_vertex), get_vertex_y(ending_vertex), color, svgFile);
    }
    
}

void print_animated_circle(double x1, double y1, List_t path,  FILE *svgFile, int flag){
    fprintf(svgFile,"\t <path d=\"M0 3.5A1.5 1.5 0 0 1 1.5 2h9A1.5 1.5 0 0 1 12 3.5V5h1.02a1.5 1.5 0 0 1 1.17.563l1.481 1.85a1.5 1.5 0 0 1 .329.938V10.5a1.5 1.5 0 0 1-1.5 1.5H14a2 2 0 1 1-4 0H5a2 2 0 1 1-3.998-.085A1.5 1.5 0 0 1 0 10.5v-7zm1.294 7.456A1.999 1.999 0 0 1 4.732 11h5.536a2.01 2.01 0 0 1 .732-.732V3.5a.5.5 0 0 0-.5-.5h-9a.5.5 0 0 0-.5.5v7a.5.5 0 0 0 .294.456zM12 10a2 2 0 0 1 1.732 1h.768a.5.5 0 0 0 .5-.5V8.35a.5.5 0 0 0-.11-.312l-1.48-1.85A.5.5 0 0 0 13.02 6H12v4zm-9 1a1 1 0 1 0 0 2 1 1 0 0 0 0-2zm9 0a1 1 0 1 0 0 2 1 1 0 0 0 0-2z\">\n");
    if(flag){
        fprintf(svgFile, "\t\t<animateMotion dur=\"8s\" repeatCount=\"indefinite\" path=\"M %lf %lf ", x1, y1);
    }else{
        fprintf(svgFile, "\t\t<animateMotion dur=\"12s\" repeatCount=\"indefinite\" path=\"M %lf %lf ", x1, y1);
    }
    for(ListNode_t node = get_list_next(get_list_first(path)); node != NULL; node = get_list_next(node)){
        fprintf(svgFile, "L %lf %lf ", get_point_x(get_list_info(node)), get_point_y(get_list_info(node)));
    }
    fprintf(svgFile, "\" fill=\"freeze\" />\n");
	fprintf(svgFile, "\t</path>\n");
}
