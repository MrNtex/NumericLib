#include "integration/trapezoid.hpp"

namespace NumericLib {
    
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
