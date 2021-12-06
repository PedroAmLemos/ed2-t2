#ifndef POINT_H_
#define POINT_H_

typedef void* Point_t;

// Cria um ponto
Point_t create_point(double x, double y);

// Ponto _a recebe o ponto _b
void assign_point(Point_t _a, Point_t _b);

// Retorna se um ponto está dentro de um retangulo passado
int is_pont_inside_rect(Point_t _point, double x, double y, double w, double h);

// Getters: Retorna o atributo do título da função.
// Setters: Altera o valor, do atributo do título da função, de uma aresta passada
double get_point_x(Point_t _point);
double get_point_y(Point_t _point);
void set_point_x(Point_t _point, double x);
void set_point_y(Point_t _point, double y);

#endif
