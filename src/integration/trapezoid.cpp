#include "integration/trapezoid.hpp"

namespace NumericLib {
    /// <summary>
	/// approximates the definite integral of a function over a given range using trapezoids method
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
    /// calculated approximation of the integral of the function over the specified range using the trapzoids method
    /// </returns>
    
    double Trapezoids(double step, double (*func)(double), const std::vector<double>& range)
    {
        double h = (range[1] - range[0]) / step;
        double i = range[0];

        double sum = 0;
        double last = func(i);
        i += h;

        while (i < range[1])
        {
            double y = func(i);
            sum += (last + y) * h;
            i += h;
            last = y;
        }

        return sum / 2;
    }

} // namespace NumericLib
