#include "interpolation/newton.hpp"
#include <vector>
#include <stdexcept>

namespace NumericLib {

    /// <summary>
    /// Evaluates a Newton interpolating polynomial at a given point x_val
    /// </summary>
    /// <param name="x_val">
	/// the point at which the polynomial is evaluated
    /// </param>
    /// <param name="x">
	/// a vector of x-coordinates of the interpolation nodes x0, x1, ..., xn
    /// </param>
    /// <param name="coefficients">
	/// a vector of coefficients of the Newton polynomial, which are computed from the divided differences a0, a1, ..., an
    /// </param>
    /// <returns>
	/// value of the Newton polynomial at the point x_val
    /// </returns>
    double evaluateNewtonPolynomial(double x_val, const std::vector<double>& x, const std::vector<double>& coefficients) {
        double result = coefficients[0];
        double product = 1.0;

        for (size_t i = 1; i < coefficients.size(); i++) {
            product *= (x_val - x[i - 1]);
            result += coefficients[i] * product;
        }

        return result;
    }

    /// <summary>
	/// Computes the coefficients of the Newton polynomial based on the divided differences of the given set of points x and y.
    /// </summary>
    /// <param name="x">
	/// itnerpolation nodes x0, x1, ..., xn
    /// </param>
    /// <param name="y">
	/// function values corresponding to the x interpolation nodes y0, y1, ..., yn
    /// </param>
    /// <returns>
	/// vector of Newton coefficients a0, a1, ..., an, where n = x.size() - 1.
    /// </returns>
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

    /// <summary>
    /// combines computing coefficients and evaluating the Newton polynomial into one step
    /// </summary>
    /// <param name="x_val">
	/// the point at which the polynomial is evaluated
    /// </param>
    /// <param name="x">
	/// the vector of x-coordinates of the interpolation nodes x0, x1, ..., xn
    /// </param>
    /// <param name="y">
	/// the vector of function values corresponding to the x interpolation nodes y0, y1, ..., yn
    /// </param>
    /// <returns>
    /// interpolated value of a function at point x_val using Newton’s divided differences interpolation method
    /// </returns>
	/// <exception cref="std::invalid_argument">
	/// thrown if the input vectors x and y do not have the same size or if they are empty
    /// </exception>
    double InterpolateNewton(double x_val, const std::vector<double>& x, const std::vector<double>& y) {
        if (x.size() != y.size() || x.empty()) {
		    throw std::invalid_argument("Input vectors must have the same non-zero size.");
	    }

        std::vector<double> coeffs = computeDividedDifferences(x, y);
        return evaluateNewtonPolynomial(x_val, x, coeffs);
    }

} // namespace NumericLib
