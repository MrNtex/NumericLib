#include "interpolation/newton.hpp"
#include <vector>

using namespace std;

double evaluateNewtonPolynomial(double x_val, const vector<double>& x, const vector<double>& coefficients) {
    double result = coefficients[0];
    double product = 1.0;

    for (size_t i = 1; i < coefficients.size(); i++) {
        product *= (x_val - x[i - 1]);
        result += coefficients[i] * product;
    }

    return result;
}

vector<double> computeDividedDifferences(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<vector<double>> table(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        table[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    vector<double> coefficients(n);
    for (int i = 0; i < n; i++) {
        coefficients[i] = table[0][i];
    }

    return coefficients;
}

double interpolate(double x_val, const vector<double>& x, const vector<double>& y) {
    vector<double> coeffs = computeDividedDifferences(x, y);
    return evaluateNewtonPolynomial(x_val, x, coeffs);
}
