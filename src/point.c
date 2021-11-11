#include <stdio.h>
#include <stdlib.h>
#include "point.h"

typedef struct Point{
    double x, y;
}Point;

Point_t create_point(double x, double y){
    Point *point = (Point*)malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    return point;
}

double get_point_x(Point_t _point){
    Point *point = (Point*)_point;
    return point->x;
}

double get_point_y(Point_t _point){
    Point *point = (Point*)_point;
    return point->y;
}

void set_point_x(Point_t _point, double x){
    Point *point = (Point*)_point;
    point->x = x;
}

void set_point_y(Point_t _point, double y){
    Point *point = (Point*)_point;
    point->y = y;
}

void assign_point(Point_t _a, Point_t _b){
    Point *a = (Point*) _a;
    Point *b = (Point*) _b;
    *a = *b;
}
