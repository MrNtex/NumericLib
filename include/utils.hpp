#pragma once

#include <string>
#include <vector>

void print_iterations(const std::string& name, const std::vector<double>& values, double root);

double GetValueHorner(double x, std::vector<double>& ai, int n = 3) {
    double value = 0;
    for (int i = n; i >= 0; i--) {
        value = value * x + ai[i];
    }
    return value;
}