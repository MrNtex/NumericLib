#pragma once
#include "integration/gauss_legendre.hpp"
#include "liniear_systems/gauss_elimination.hpp"
#include <vector>
#include <iostream>
#include <cmath>

namespace NumericLib {

template <typename Func>
class Approximation {
    Func function;
    std::vector<double> coeffs;
    int degree;
    std::vector<double> range;

public:
    Approximation(Func func, int deg, std::vector<double> r);

    double Approximate(double x);
    double operator()(double x);
    void PrintCoeffs();
};

} // namespace NumericLib
