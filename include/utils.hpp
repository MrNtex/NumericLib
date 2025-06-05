#pragma once

#include <string>
#include <vector>

namespace NumericLib {

void print_iterations(const std::string& name, const std::vector<double>& values, double root) {
    std::cout << "\nPrzyblizenia (" << name << ") [|x_n - x*|]:\n";
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << "Iteracja " << i + 1 << ": " << std::setw(12) << values[i]
            << "  Blad: " << std::abs(values[i] - root) << "\n";
    }
}

double GetValueHorner(double x, std::vector<double>& ai, int n = 3) {
    double value = 0;
    for (int i = n; i >= 0; i--) {
        value = value * x + ai[i];
    }
    return value;
}

} // namespace NumericLib