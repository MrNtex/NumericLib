#pragma once
#include <vector>

namespace NumericLib {
double Simpson(int split, double (*func)(double), const std::vector<double>& range);
} // namespace NumericLib
