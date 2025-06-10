#include <iostream>
#include <vector>
#include <cmath>
#include <NumericLib.hpp>

#define M_PI 3.14159265358979323846

using namespace NumericLib;

int main() {
    std::cout << "NumericLib - Examples of Numerical Methods\n";
    std::cout << "=========================================\n\n";

    // 1. Integration Methods Example
    std::cout << "1. Integration Methods:\n";
    std::cout << "------------------------\n";
    
    auto func = [](double x) { return sin(x) * exp(-x); };
    std::vector<double> range = {0.0, M_PI};
    int steps = 1000;

    double rectResult = Rect(steps, func, range);
    double simpsonResult = Simpson(steps, func, range);
    double trapezoidResult = Trapezoids(steps, func, range);
    double gaussResult = GaussLegendre(func, range);

    std::cout << "Integral of sin(x)*exp(-x) from 0 to pi:\n";
    std::cout << "Rectangle method: " << rectResult << "\n";
    std::cout << "Simpson's rule: " << simpsonResult << "\n";
    std::cout << "Trapezoidal rule: " << trapezoidResult << "\n";
    std::cout << "Gauss-Legendre: " << gaussResult << "\n\n";

    // 2. Interpolation Example
    std::cout << "2. Interpolation Methods:\n";
    std::cout << "------------------------\n";
    
    std::vector<double> x_points = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y_points = {1.0, 2.0, 4.0, 8.0, 16.0};
    double x_interp = 2.5;

    double lagrangeResult = Lagrange(x_points, y_points, x_interp);
    double newtonResult = Newton(x_points, y_points, x_interp);

    std::cout << "Interpolation at x = 2.5:\n";
    std::cout << "Lagrange method: " << lagrangeResult << "\n";
    std::cout << "Newton method: " << newtonResult << "\n\n";

    // 3. Gauss Elimination Example
    std::cout << "3. Gauss Elimination:\n";
    std::cout << "--------------------\n";
    
    std::vector<std::vector<double>> A = {
        {2.0, 1.0, -1.0},
        {1.0, 3.0, 2.0},
        {3.0, 2.0, 1.0}
    };
    std::vector<double> b = {4.0, 7.0, 8.0};
    std::vector<double> x(3);

    if (GaussElimination(A, b, x)) {
        std::cout << "Solution of the system:\n";
        for (size_t i = 0; i < x.size(); ++i) {
            std::cout << "x" << i + 1 << " = " << x[i] << "\n";
        }
    }
    std::cout << "\n";

    // 4. Approximation Example
    std::cout << "4. Least Squares Approximation:\n";
    std::cout << "------------------------------\n";
    
    std::vector<double> x_data = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y_data = {1.0, 1.5, 2.0, 2.5, 3.0};
    
    auto [a, b_coef] = LeastSquares(x_data, y_data);
    std::cout << "Linear fit: y = " << a << "x + " << b_coef << "\n";

    return 0;
} 