#ifndef INTERPOLATION_FUNCTIONS_HPP_INCLUDED
#define INTERPOLATION_FUNCTIONS_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <math.h>
#include "Point.h"

std::vector<long double> count_function(std::vector<Point>);
std::vector<long double> polynomial_multiplication(const std::vector<long double>&, const std::vector<long double>&);
std::vector<long double> polynomial_sum(const std::vector<long double>&, const std::vector<long double>&);
double interpolation_function(double arg, const std::vector<long double>&);

#endif
