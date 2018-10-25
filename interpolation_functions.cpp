#include "interpolation_functions.hpp"

using namespace std;

vector<double> count_function(vector<double> xs, vector<double> ys) {
    typedef vector<double>::size_type size;
    size sz = xs.size();
    vector<double>final_polynom = {0};
    for (int i = 0; i < sz; ++i) {
        double denominator = 1;
        vector<double> nominator = {1};
        for (int j = 0; j < sz; ++j) {
            if (i != j) {
                denominator *= (xs[i] - xs[j]);
                vector<double>current_polynom = {(-1)*xs[j], 1};
                nominator = polynomial_multiplication(nominator, current_polynom);
            }
        }
        vector<double>denom = {1/denominator};
        nominator = polynomial_multiplication(nominator, denom);
        vector<double>y_value = {ys[i]};
        nominator = polynomial_multiplication(nominator, y_value);
        final_polynom = polynomial_sum(final_polynom, nominator);
    }
    return final_polynom;
}

/*
    Two vectors represent two polynomials, indexes are x powers, values are coefficients
*/
vector<double> polynomial_multiplication(const vector<double>& first, const vector<double>& second) {
    typedef vector<double>::size_type size;
    size sz = first.size() + second.size() - 1;
    vector<double>results;
    for (int i = 0; i < sz; ++i) {
        results.push_back(0);
    }
    for (int i = 0; i < first.size(); ++i) {
        for (int j = 0; j < second.size(); ++j) {
            double value = first[i]*second[j];
            int index = i+j;
            results[index] += value;
        }
    }
    return results;
}

vector<double> polynomial_sum(const vector<double>& first, const vector<double>& second) {
    typedef vector<double>::size_type size;
    size sz = max(first.size(), second.size());
    vector<double>results;
    for (int i = 0; i < sz; ++i) {
        double val = 0;
        if (i < first.size())
            val += first[i];
        if (i < second.size())
            val += second[i];
        results.push_back(val);
    }
    return results;
}

double interpolation_function(double arg, const vector<double>& coefficients) {
    size_t sz = coefficients.size();
    double result = 0;
    for (size_t i = 0; i < sz; i++) {
        result += coefficients[i] * pow(arg, i);
    }
    return result;
}
