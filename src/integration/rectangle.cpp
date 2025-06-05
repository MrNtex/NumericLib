#include "integration/rectangle.hpp"

namespace NumericLib {

double Rect(double step, double (*func)(double), const std::vector<double>& range)
{
    double h = (range[1] - range[0]) / step;
    double i = range[0];

    double sum = 0;

    while (i < range[1])
    {
        sum += func(i) * h;
        i += h;
    }

    return sum;
}

} // namespace NumericLib