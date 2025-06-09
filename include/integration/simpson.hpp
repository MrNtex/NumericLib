#pragma once
#include <vector>

namespace NumericLib {
    /// <summary>
    /// approximates the definite integral of a function over a given range using simpson's method
    /// </summary>
    /// <param name="split">
    /// number of intervals to split the range into 
    /// </param>
    /// <param name="func">
    /// double pointer to a function to integrate
    /// </param>
    /// <param name="range">
    /// vector of two doubles [a , b] representing the start and end of integration
    /// </param>
    /// <returns>
    /// calculated approximation of the integral of the function over the specified range using simpsons's method
    /// </returns>
	double Simpson(int split, double (*func)(double), const std::vector<double>& range);
} // namespace NumericLib
