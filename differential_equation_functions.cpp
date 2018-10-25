#include "differential_equation_functions.hpp"
#include <math.h>

using namespace std;

vector<Point>solve_equation(double func(double, double), double X0, double Y0, double x_max, double inaccuracy) {
    vector<Point> to_ret;
    //double x = X0;
    double y = Y0;
    double step = sqrt(inaccuracy);
    Point* first = new Point(X0, Y0);
    to_ret.push_back(*first);

    for (double x = X0; x <= x_max; x = x + step) {
        double delta_y = step*func(x - step/2, y + step/2*func(x - step, y));
        y += delta_y;
        Point* pnt = new Point(x, y);
        to_ret.push_back(*pnt);
    }
    return to_ret;
}
