#include "interpolation/lagrange.hpp"
#include <stdexcept>

namespace NumericLib {

    double InterpolateLagrange(double x, const std::vector<double>& xi, const std::vector<double>& fxi, int prec)
    {
        if (xi.size() != fxi.size() || xi.empty()) {
            throw std::invalid_argument("Input vectors must have the same non-zero size.");
        }

        double sum = 0;

        for (int i = 0; i < xi.size(); i += prec)
        {
            double y = fxi[i];
            double pi = 1;

            for (int j = 0; j < fxi.size(); j += prec)
            {
                if (i == j) continue;
                double frac = (x - xi[j]) / (xi[i] - xi[j]);

                pi *= frac;
            }

            sum += pi * y;
        }

        return sum;
    }

} // namespace NumericLib
