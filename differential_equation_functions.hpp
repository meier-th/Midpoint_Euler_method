#ifndef DIFFERENTIAL_EQUATION_FUNCTIONS_HPP_INCLUDED
#define DIFFERENTIAL_EQUATION_FUNCTIONS_HPP_INCLUDED
#include <vector>
#include "Point.h"

std::vector<Point> solve_equation(double funct(double, double), double X0, double Y0, double x_max, double inaccuracy);

#endif
