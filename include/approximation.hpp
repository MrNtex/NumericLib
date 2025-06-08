#pragma once

#include <vector>
#include <cmath>
#include <iostream>

namespace NumericLib {
    template <typename Func>
    class Approximation
    {
        Func function;
        std::vector<double> coeffs;
        int degree;
        std::vector<double> range;

    public:
        Approximation(Func func, int deg, std::vector<double> r) : function(func), degree(deg), range(r)
        {
            if (range.size() != 2 || range[0] >= range[1]) {
                throw std::invalid_argument("Invalid range: range must be [a, b] with a < b.");
            }

            if (deg < 0) {
                throw std::invalid_argument("Degree must be non-negative.");
            }

            coeffs.resize(degree + 1);
            std::vector<std::vector<double>> A(degree + 1, std::vector<double>(degree + 1));
            std::vector<double> b(degree + 1);

            // macierz A - analitycznie
            for (int i = 0; i <= degree; i++) {
                for (int j = 0; j <= degree; j++) {
                    int power = i + j;
                    A[i][j] = (std::pow(range[1], power + 1) - std::pow(range[0], power + 1)) / (power + 1);
                }
            }

            // wektor B - Gauss-Legendre
            for (int i = 0; i <= degree; i++) {
                b[i] = gaussLegendreIntegralSplit(range[0], range[1], [this, i](double x) {
                    return this->function(x) * std::pow(x, i);
                    }, 4, 10);
            }

            coeffs = GaussElimination(A, b);
        }

        double Approximate(double x)
        {
            double result = 0.0;
            for (int i = 0; i < coeffs.size(); i++)
            {
                result += coeffs[i] * std::pow(x, i);
            }
            return result;
        }

        double operator()(double x)
        {
            return Approximate(x);
        }

        void PrintCoeffs()
        {
            std::cout << "Wspolczynniki wielomianu:\n";
            for (int i = 0; i < coeffs.size(); i++)
            {
                std::cout << "a[" << i << "] = " << coeffs[i] << "\n";
            }
        }
    };
}

