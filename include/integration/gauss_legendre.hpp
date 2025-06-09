#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

namespace NumericLib {

    /// <summary>
	/// struct representing the nodes and weights for the Gauss-Legendre quadrature rule
    /// </summary>
    struct GaussLegendreRule {
        std::vector<double> nodes;
        std::vector<double> weights;
    };

    /// <summary>
	/// inline function to get the Gauss-Legendre quadrature rule for a given number of nodes
    /// </summary>
    /// <param name="n">
	/// number of nodes for the Gauss-Legendre quadrature rule for 2, 3 and 4
    /// </param>
    /// <returns>
	/// struct containing the nodes and weights for the Gauss-Legendre quadrature rule
    /// </returns>
	/// <exception cref="std::invalid_argument">
	/// thrown if the input n is not one of the supported values: 2,3 or 4
    /// </exception>
    inline GaussLegendreRule getGLRule(int n) {
        switch (n) {
        case 2:
            return { {-0.5773502692, 0.5773502692}, {1.0, 1.0} };
        case 3:
            return { {-0.7745966692, 0.0, 0.7745966692}, {0.5555555556, 0.8888888889, 0.5555555556} };
        case 4:
            return {
                {-0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116},
                {0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451}
            };
        default:
            throw std::invalid_argument("Obslugiwane tylko 2, 3, 4 wezly.");
        }
    }

    /// <summary>
	/// computes the definite integral of a function using the Gauss-Legendre quadrature method over the interval [a, b] with n nodes
    /// </summary>
    /// <typeparam name="Func">
	/// template type for the function to be integrated, which should accept a double and return a double
    /// </typeparam>
    /// <param name="a">
	/// lower limit of the integral
    /// </param>
    /// <param name="b">
	/// upper limit of the integral
    /// </param>
    /// <param name="func">
    /// funtion to be integrated
    /// </param>
    /// <param name="n">
	/// number of nodes to be used in the Gauss-Legendre quadrature method
    /// </param>
    /// <returns>
    /// approximate value of the definite integral
    /// </returns>
    template <typename Func>
    double gaussLegendreIntegral(double a, double b, Func func, int n) {
        GaussLegendreRule rule = getGLRule(n);
        double sum = 0.0;

        for (int i = 0; i < rule.nodes.size(); i++) {
            double xi = ((b - a) / 2.0) * rule.nodes[i] + (a + b) / 2.0;
            sum += rule.weights[i] * func(xi);
        }

        return ((b - a) / 2.0) * sum;
    }

    /// <summary>
	/// computes the definite integral of a function using the Gauss-Legendre quadrature method over the interval [a, b] with n nodes, splitting the interval into smaller segments
    /// </summary>
    /// <typeparam name="Func">
    /// template type for the function to be integrated, which should accept a double and return a double
    /// </typeparam>
    /// <param name="a">
	/// lower limit of the integral
    /// </param>
    /// <param name="b">
	/// upper limit of the integral
    /// </param>
    /// <param name="func">
	/// function to be integrated
    /// </param>
    /// <param name="n">
	/// number of nodes to be used in the Gauss-Legendre quadrature method
    /// </param>
    /// <param name="splits">
	/// number of splits, subintervals to divide the interval [a, b] into smaller parts for more accurate integration
    /// </param>
    /// <returns>
    /// total approximate value of the definite integral over [a, b]
    /// </returns>
    template <typename Func>
        double gaussLegendreIntegralSplit(double a, double b, Func func, int n, int splits) {
            double h = (b - a) / splits;
            double sum = 0.0;

            for (int i = 0; i < splits; ++i) {
                double ai = a + i * h;
                double bi = ai + h;
                sum += gaussLegendreIntegral(ai, bi, func, n);
            }

            return sum;
        }

} // namespace NumericLib
