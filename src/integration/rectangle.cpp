#include "integration/rectangle.hpp"

namespace NumericLib {

    double Rect(double step, double (*func)(double), const std::vector<double>& range)
    {
        if (range.size() != 2)
            throw std::invalid_argument("Range vector must have exactly two elements.");
        if (step <= 0)
            throw std::invalid_argument("Step size must be positive.");
        if (range[0] >= range[1])
            throw std::invalid_argument("Range start must be less than range end.");

        double h = (range[1] - range[0]) / step;
        double i = range[0];

        double sum = 0;

        while (i < range[1])
        {
            double y = func(i);
            if (!std::isfinite(y))
                throw std::domain_error("Function evaluation returned non-finite value.");

            sum += func(i) * h;
            i += h;
        }

        return sum;
    }

} // namespace NumericLib