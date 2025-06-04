#pragma once
#include "gauss_legendre.hpp"
#include "gauss_elimination.hpp"
#include <vector>
#include <iostream>
#include <cmath>

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
