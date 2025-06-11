#pragma once
#include <vector>
#include <stdexcept>
#include <vector>
#include <cmath>

namespace NumericLib {
    /// <summary>
    /// approximates the integral of a function using the rectangle method
    /// </summary>
    /// <param name="step">
    /// number of rectangles,steps to use for the approximation
    /// </param>
    /// <param name="func">
    /// double pointer to a function to integrate
    /// </param>
    /// <param name="range">
    /// vector of two doubles [a , b] representing the start and end of integration
    /// </param>
    /// <returns>
    /// calculated approximation of the integral of the function over the specified range using the rectangle method
    /// </returns>
    /// @exception std::invalid_argument thrown if the input range does not contain exactly two elements in the correct order 
	double Rect(double step, double (*func)(double), const std::vector<double>& range);
} // namespace NumericLib
