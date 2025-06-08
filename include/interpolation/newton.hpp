#pragma once
#include <vector>

namespace NumericLib {
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

	double InterpolateNewton(double x_val, const std::vector<double>& x, const std::vector<double>& y);

} // namespace NumericLib