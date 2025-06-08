#pragma once
#include <vector>

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
	double InterpolateLagrange(double x, const std::vector<double>& xi, const std::vector<double>& fxi, int prec);

} // namespace NumericLib