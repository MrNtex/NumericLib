#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

void print_iterations(const std::string& name, const std::vector<double>& values, double root) {
    std::cout << "\nPrzyblizenia (" << name << ") [|x_n - x*|]:\n";
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << "Iteracja " << i + 1 << ": " << std::setw(12) << values[i]
            << "  Blad: " << std::abs(values[i] - root) << "\n";
    }
}
