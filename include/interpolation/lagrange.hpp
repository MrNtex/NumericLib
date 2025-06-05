#pragma once
#include <vector>

namespace NumericLib {

double InterpolateLagrange(double x, const std::vector<double>& xi, const std::vector<double>& fxi, int prec);

} // namespace NumericLib