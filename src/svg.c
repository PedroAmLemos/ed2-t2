#include "svg.h"
#include <stdio.h>

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

void print_text(double x, double y, char text[], FILE *svgFile){
   fprintf(svgFile, "\t<text x=\"%.2f\" y=\"%.2f\">%s</text>\n", x, y, text);
}

void print_circle(double cx, double cy, double r, char stroke[], char fill[], char sw[], FILE *svgFile){
    fprintf(svgFile, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", cx, cy, r, stroke, fill, sw);
}

void print_rectangle_dashed(double x, double y, double w, double h, FILE *svgFile){
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" opacity=\"0.8\" fill=\"none\" stroke=\"black\" stroke-width=\"3px\" stroke-dasharray=\"20\"/>\n", x, y, w, h);
}

void print_rectangle(double x, double y, double w, double h, char *fill, char *stroke, FILE *svgFile){
    fprintf(svgFile,"\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" opacity=\"0.8\" fill=\"%s\" stroke=\"%s\" stroke-width=\"3px\" />\n", x, y, w, h, fill, stroke);
}
