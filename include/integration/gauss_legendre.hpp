#pragma once
#include <vector>
#include <stdexcept>

struct GaussLegendreRule {
    std::vector<double> nodes;
    std::vector<double> weights;
};

GaussLegendreRule getGLRule(int n);
template<typename Func>
double gaussLegendreIntegral(double a, double b, Func func, int n);
template<typename Func>
double gaussLegendreIntegralSplit(double a, double b, Func func, int n, int splits);
