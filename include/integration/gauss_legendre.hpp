#pragma once
#include <vector>
#include <stdexcept>

namespace NumericLib {

struct GaussLegendreRule {
    std::vector<double> nodes;
    std::vector<double> weights;
};

GaussLegendreRule getGLRule(int n);
double gaussLegendreIntegral(double a, double b, double (*func)(double), int n);
double gaussLegendreIntegralSplit(double a, double b, double (*func)(double), int n, int splits);

} // namespace NumericLib
