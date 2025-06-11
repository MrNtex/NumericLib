#include "../include/utils.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

namespace NumericLib {

    void print_iterations(const std::string& name, const std::vector<double>& values, double root) {
        std::cout << "\nPrzyblizenia (" << name << ") [|x_n - x*|]:\n";
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << "Iteracja " << i + 1 << ": " << std::setw(12) << values[i]
                << "  Blad: " << std::abs(values[i] - root) << "\n";
        }
    }

    double GetValueHorner(double x, std::vector<double>& ai, int n) {
        double value = 0;
        for (int i = n; i >= 0; i--) {
            value = value * x + ai[i];
        }
        return value;
    }

    void PrintMatrix(std::vector<std::vector<double>>& A) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(10) << A[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void PrintMatrix(std::vector<std::vector<double>>& A, std::vector<double>& b) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(10) << A[i][j] << " ";
            }
            std::cout << "| " << b[i] << std::endl;
        }
        std::cout << std::endl;
    }

    bool VerifyMatrix(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                sum += x[j] * A[i][j];
            }
            if (std::abs(sum - b[i]) > 1e-5) return false;
        }
        return true;
    }

} // namespace NumericLib 