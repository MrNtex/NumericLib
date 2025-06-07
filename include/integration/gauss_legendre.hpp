#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

namespace NumericLib {

    struct GaussLegendreRule {
        std::vector<double> nodes;
        std::vector<double> weights;
    };

    inline GaussLegendreRule getGLRule(int n) {
        switch (n) {
        case 2:
            return { {-0.5773502692, 0.5773502692}, {1.0, 1.0} };
        case 3:
            return { {-0.7745966692, 0.0, 0.7745966692}, {0.5555555556, 0.8888888889, 0.5555555556} };
        case 4:
            return {
                {-0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116},
                {0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451}
            };
        default:
            throw std::invalid_argument("Obslugiwane tylko 2, 3, 4 wezly.");
        }
    }

    template <typename Func>
    double gaussLegendreIntegral(double a, double b, Func func, int n) {
        GaussLegendreRule rule = getGLRule(n);
        double sum = 0.0;

        for (int i = 0; i < rule.nodes.size(); i++) {
            double xi = ((b - a) / 2.0) * rule.nodes[i] + (a + b) / 2.0;
            sum += rule.weights[i] * func(xi);
        }

        return ((b - a) / 2.0) * sum;
    }

    template <typename Func>
    double gaussLegendreIntegralSplit(double a, double b, Func func, int n, int splits) {
        double h = (b - a) / splits;
        double sum = 0.0;

        for (int i = 0; i < splits; ++i) {
            double ai = a + i * h;
            double bi = ai + h;
            sum += gaussLegendreIntegral(ai, bi, func, n);
        }

        return sum;
    }

} // namespace NumericLib
