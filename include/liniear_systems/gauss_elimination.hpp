#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace NumericLib {

std::vector<double> GaussElimination(std::vector<std::vector<double>>& A, std::vector<double>& b);

} // namespace NumericLib
