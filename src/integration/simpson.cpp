#include "integration/simpson.hpp"

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
    /// 
    double Simpson(int split, double (*func)(double), const std::vector<double>& range)
    {
        if (split % 2 == 1) split++;

        double h = (range[1] - range[0]) / (double)split;
        double sum = func(range[1]) + func(range[0]);

        for (int i = 1; i < split; i++) {
            double x = range[0] + i * h;
            if (i % 2 == 0) {
                sum += 2 * func(x);
            }
            else {
                sum += 4 * func(x);
            }
        }

        return sum * h / 3;
}

} // namespace NumericLib