#include "interpolation/newton.hpp"
#include <vector>
#include <stdexcept>

namespace NumericLib {

double evaluateNewtonPolynomial(double x_val, const std::vector<double>& x, const std::vector<double>& coefficients) {
    double result = coefficients[0];
    double product = 1.0;

    for (size_t i = 1; i < coefficients.size(); i++) {
        product *= (x_val - x[i - 1]);
        result += coefficients[i] * product;
    }

    return result;
}

std::vector<double> computeDividedDifferences(const std::vector<double>& x, const std::vector<double>& y) {
    int n = x.size();
    std::vector<std::vector<double>> table(n, std::vector<double>(n));

    for (int i = 0; i < n; i++) {
        table[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    std::vector<double> coefficients(n);
    for (int i = 0; i < n; i++) {
        coefficients[i] = table[0][i];
    }

    return coefficients;
}

double InterpolateNewton(double x_val, const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size() || x.empty()) {
		throw std::invalid_argument("Input vectors must have the same non-zero size.");
	}

    std::vector<double> coeffs = computeDividedDifferences(x, y);
    return evaluateNewtonPolynomial(x_val, x, coeffs);
}

} // namespace NumericLib
