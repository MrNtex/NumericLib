#include "integration/simpson.hpp"

namespace NumericLib {

    double Simpson(int split, double (*func)(double), const std::vector<double>& range)
    {
        if (range.size() != 2)
			throw std::invalid_argument("Range vector must have exactly two elements.");
        if (split <= 0)
            throw std::invalid_argument("Number of splits must be positive.");
        if (range[0] >= range[1])
            throw std::invalid_argument("Range start must be less than range end.");


        if (split % 2 == 1) split++;

        double h = (range[1] - range[0]) / (double)split;
        double sum = func(range[1]) + func(range[0]);

        for (int i = 1; i < split; i++) {
            double x = range[0] + i * h;
            double y = func(x);
            if (!std::isfinite(y))
				throw std::domain_error("Function evaluation returned non-finite value.");
            if (i % 2 == 0) {
                sum += 2 * y;
            }
            else {
                sum += 4 * y;
            }
        }

        return sum * h / 3;
}

} // namespace NumericLib