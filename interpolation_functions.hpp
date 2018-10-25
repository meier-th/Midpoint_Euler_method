#ifndef INTERPOLATION_FUNCTIONS_HPP_INCLUDED
#define INTERPOLATION_FUNCTIONS_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <math.h>

std::vector<double> count_function(std::vector<double>, std::vector<double>);
std::vector<double> polynomial_multiplication(const std::vector<double>&, const std::vector<double>&);
std::vector<double> polynomial_sum(const std::vector<double>&, const std::vector<double>&);
double interpolation_function(double arg, const std::vector<double>&);

#endif
