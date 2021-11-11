#ifndef POINT_H_
#define POINT_H_

typedef void* Point_t;

Point_t create_point(double x, double y);

double get_point_x(Point_t _point);

double get_point_y(Point_t _point);

void set_point_x(Point_t _point, double x);

void set_point_y(Point_t _point, double y);

void assign_point(Point_t _a, Point_t _b);

int is_pont_inside_rect(Point_t _point, double x, double y, double w, double h);

#endif
