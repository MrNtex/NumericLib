#pragma once
#include <vector>
#include <iomanip>
#include <numeric>

namespace NumericLib {

void pivot(std::vector<std::vector<double>>& A, std::vector<double>& b, int k);

void luDecomposition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L,
    std::vector<std::vector<double>>& U, std::vector<double>& b);

std::vector<double> forwardSubstitution(const std::vector<std::vector<double>>& L, const std::vector<double>& b);

std::vector<double> backwardSubstitution(const std::vector<std::vector<double>>& U, const std::vector<double>& z);

std::vector<double> solveWithFullPivotLU(std::vector<std::vector<double>> A, std::vector<double> b);

} // namespace NumericLib
