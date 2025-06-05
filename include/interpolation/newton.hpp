#pragma once
#include <vector>

namespace NumericLib {

double InterpolateNewton(double x_val, const std::vector<double>& x, const std::vector<double>& y);

} // namespace NumericLib