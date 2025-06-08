#include "interpolation/lagrange.hpp"
#include <stdexcept>

namespace NumericLib {
    /// <summary>
	/// calculates the Lagrange interpolation at a given point x using the provided nodes and function value
    /// </summary>
    /// <param name="x">
	/// point used at which the function value is to be calculated
    /// </param>
    /// <param name="xi">
    /// x-coordinates of the interpolation nodes
    /// </param>
    /// <param name="fxi">
	/// y-coordinates of the interpolation nodes which correspond to the x-coordinates
    /// </param>
    /// <param name="prec">
	/// the step size for the interpolation, which determines how many points are used in the interpolation
    /// </param>
    /// <returns>
	/// Interpolated value at point x using Lagrange interpolation method.
    /// </returns>
	/// <exception cref="std::invalid_argument">
	/// thrown if the input vectors xi and fxi arguments do not have the same size or if they are empty
    /// </exception>

    double InterpolateLagrange(double x, const std::vector<double>& xi, const std::vector<double>& fxi, int prec)
    {
        if (xi.size() != fxi.size() || xi.empty()) {
            throw std::invalid_argument("Input vectors must have the same non-zero size.");
        }

        double sum = 0;

        for (int i = 0; i < xi.size(); i += prec)
        {
            double y = fxi[i];
            double pi = 1;

            for (int j = 0; j < fxi.size(); j += prec)
            {
                if (i == j) continue;
                double frac = (x - xi[j]) / (xi[i] - xi[j]);

                pi *= frac;
            }

            sum += pi * y;
        }

        return sum;
    }

} // namespace NumericLib
