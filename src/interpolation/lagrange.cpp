#include "interpolation/lagrange.hpp"
#include <stdexcept>

namespace NumericLib {

    double InterpolateLagrange(double x, const std::vector<double>& xi, const std::vector<double>& fxi, int prec)
    {
        if (xi.size() != fxi.size() || xi.empty()) {
            throw std::invalid_argument("Input vectors must have the same non-zero size.");
        }

        if (prec > xi.size()) {
            throw std::invalid_argument("Parameter 'prec' exceeds the number of available points.");
        }

        double sum = 0;

        for (int i = 0; i < prec; ++i)
        {
            double y = fxi[i];
            double pi = 1.0;

            for (int j = 0; j < prec; ++j)
            {
                if (i == j) continue;
                pi *= (x - xi[j]) / (xi[i] - xi[j]);
            }

            sum += pi * y;
        }

        return sum;
    }

} // namespace NumericLib
