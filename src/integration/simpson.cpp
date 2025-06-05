#include "integration/simpson.hpp"

namespace NumericLib {

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