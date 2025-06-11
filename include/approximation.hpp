#pragma once

#include <vector>
#include <cmath>
#include <iostream>

namespace NumericLib {

    /// <summary>
    /// Constructs a polynomial least-squares approximation of a given function over a specified interval.
    /// </summary>
    /// <typeparam name="Func">
    /// A callable object representing the function to approximate (e.g., lambda, function pointer).
    /// </typeparam>
    template <typename Func>
    class Approximation
    {
        Func function;
        std::vector<double> coeffs;
        int degree;
        std::vector<double> range;

    public:
        /// <summary>
        /// Creates an approximation object by computing the polynomial coefficients using the least-squares method.
        /// </summary>
        /// <param name="func">
        /// Function to approximate.
        /// </param>
        /// <param name="deg">
        /// Degree of the approximating polynomial. Must be non-negative.
        /// </param>
        /// <param name="r">
        /// Vector of two doubles [a, b] specifying the interval over which to approximate the function.
        /// </param>
        /// <exception cref="std::invalid_argument">
        /// Thrown if the interval is invalid or degree is negative.
        /// </exception>
        Approximation(Func func, int deg, std::vector<double> r) : function(func), degree(deg), range(r)
        {
            if (range.size() != 2 || range[0] >= range[1]) {
                throw std::invalid_argument("Invalid range: range must be [a, b] with a < b.");
            }

            if (deg < 0) {
                throw std::invalid_argument("Degree must be non-negative.");
            }

            coeffs.resize(degree + 1);
            std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1));
            std::vector<double> b(degree + 1);

            // Fill matrix A analytically
            for (int i = 0; i <= degree; i++) {
                for (int j = 0; j <= degree; j++) {
                    int power = i + j;
                    A[i][j] = (std::pow(range[1], power + 1) - std::pow(range[0], power + 1)) / (power + 1);
                }
            }

            // Fill vector b using Gauss-Legendre quadrature
            for (int i = 0; i <= degree; i++) {
                b[i] = gaussLegendreIntegralSplit(range[0], range[1], [this, i](double x) {
                    return this->function(x) * std::pow(x, i);
                    }, 4, 10);
            }

            coeffs = GaussElimination(A, b);
        }

        /// <summary>
        /// Evaluates the approximating polynomial at a given point x.
        /// </summary>
        /// <param name="x">
        /// The input value at which to evaluate the approximation.
        /// </param>
        /// <returns>
        /// The value of the approximating polynomial at point x.
        /// </returns>
        double Approximate(double x)
        {
            double result = 0.0;
            for (int i = 0; i < coeffs.size(); i++)
            {
                result += coeffs[i] * std::pow(x, i);
            }
            return result;
        }

        /// <summary>
        /// Function-call operator overload for evaluating the approximation.
        /// </summary>
        /// <param name="x">
        /// The input value at which to evaluate the approximation.
        /// </param>
        /// <returns>
        /// The value of the approximating polynomial at point x.
        /// </returns>
        double operator()(double x)
        {
            return Approximate(x);
        }

        /// <summary>
        /// Prints the coefficients of the approximating polynomial to the standard output.
        /// </summary>
        void PrintCoeffs()
        {
            std::cout << "Polynomial coefficients:\n";
            for (int i = 0; i < coeffs.size(); i++)
            {
                std::cout << "a[" << i << "] = " << coeffs[i] << "\n";
            }
        }
    };

} // namespace NumericLib
