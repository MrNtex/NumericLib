#pragma once
#include <vector>

namespace NumericLib {
double Trapezoids(double step, double (*func)(double), const std::vector<double>& range);
} // namespace NumericLib
