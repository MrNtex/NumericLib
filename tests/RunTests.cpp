#include "Test.h"
#include "NumericLib.hpp"

#define tol 0.01
using namespace NumericLib;

double testFunc(double x) {
    return x * x - 1;
}

double infiniteFunc(double x) {
	return 1.0 / x;
}

void RunTests() {
    {
        UnitGroup interpolation("Interpolation");

        std::vector<double> x = { 1, 2, 3 };
        std::vector<double> y = { 2, 3, 5 };

        double res = InterpolateLagrange(2.5, x, y, 4);
        interpolation.AddTest("Lagrange - Correct input", std::abs(res - 3.875) < tol);

        std::vector<double> badX = { 1, 2 };
        std::vector<double> badY = { 2, 3, 4 };

        interpolation.AddTest("Lagrange - Mismatched sizes", shouldThrowException([&]() {
            InterpolateLagrange(2.0, badX, badY, 1);
            }));

        x = { 1, 2, 3 };
        y = { 2, 3, 5 };

        res = InterpolateNewton(2.5, x, y);
        interpolation.AddTest("Newton - Correct input", std::abs(res - 3.875) < tol);

        interpolation.AddTest("Newton - Empty input", shouldThrowException([&]() {
            InterpolateNewton(2.0, {}, {});
            }));
    }

    {
        UnitGroup nonliniear("Nonliniear Methods");

        double res = bisection(testFunc, 0.0, 2.0);
        nonliniear.AddTest("Bisection - Correct input", std::abs(res - 1.0) < tol);

        nonliniear.AddTest("Bisection - No sign change", shouldThrowException([&]() {
            bisection(testFunc, 2.0, 3.0);
            }));


        res = newton(testFunc, 1.0, [](double x) { return 2 * x; });

        nonliniear.AddTest("Newton - Correct input", std::abs(res - 1.0) < tol);
        nonliniear.AddTest("Newton - Zero derivative", shouldThrowException([&]() {
            newton(testFunc, 0.0, [](double x) { return 0; });
            }));

        res = newton_numeric(testFunc, 1.0);
        nonliniear.AddTest("Newton Numeric - Correct input", std::abs(res - 1.0) < tol);
        nonliniear.AddTest("Newton Numeric - Zero derivative", shouldThrowException([&]() {
            newton_numeric(testFunc, 0.0);
            }));

        res = secant(testFunc, 0.0, 2.0, -1.0, 3.0);
        nonliniear.AddTest("Secant - Correct input", std::abs(res - 1.0) < tol);
        nonliniear.AddTest("Secant - Division by zero", shouldThrowException([&]() {
            secant(testFunc, -.5, .5, -1, 1.5);
            }));

        res = falsi(testFunc, 0.0, 2.0);
        nonliniear.AddTest("Falsi - Correct input", std::abs(res - 1.0) < tol);
        nonliniear.AddTest("Falsi - No sign change", shouldThrowException([&]() {
            falsi(testFunc, -.5, .5);
            }));

    }

    {
        UnitGroup linearSystems("Linear Systems");

        std::vector<std::vector<double>> A = { {2, 1}, {1, 3} };
        std::vector<double> b = { 5, 7 };
        std::vector<double> x;

        x = GaussElimination(A, b);
        linearSystems.AddTest("Gauss Elimination - Correct input", VerifyMatrix(A, b, x));

        A = { {2, 1}, {6, 3} };
        b = { 5, 7 };
        linearSystems.AddTest("Gauss Elimination - Singular matrix", shouldThrowException([&]() {
            GaussElimination(A, b);
            }));

        A = { {2, 1}, {1, 3} };
        b = { 5, 7 };
        x = solveWithFullPivotLU(A, b);
        linearSystems.AddTest("LU Decomposition - Correct input", VerifyMatrix(A, b, x));

        A = { {2, 1}, {6, 3} };
        b = { 5, 7 };
        linearSystems.AddTest("LU Decomposition - Singular matrix", shouldThrowException([&]() {
            solveWithFullPivotLU(A, b);
            }));
    }

    {
        UnitGroup integration("Integration");

        auto f = [](double x) { return x * x; };

        double res = Trapezoids(10000, f, { 0.0, 2.0 });
        integration.AddTest("Trapezoid - Correct input", std::abs(res - (8.0 / 3.0)) < tol);
        integration.AddTest("Trapezoid - Empty range", shouldThrowException([&]() {
			Trapezoids(10000, f, {});
			}));

        res = Simpson(100, f, { 0.0, 2.0 });
        integration.AddTest("Simpson - Correct input", std::abs(res - (8.0 / 3.0)) < tol);
        integration.AddTest("Simpson - Incorrect range", shouldThrowException([&]() {
			Simpson(100, f, {1,-3});
			}));

        res = Rect(10000, f, { 0.0, 2.0 });
        integration.AddTest("Rectangle - Correct input", std::abs(res - (8.0 / 3.0)) < tol);
        integration.AddTest("Rectangle - Infinite value", shouldThrowException([&]() {
            Rect(10000, infiniteFunc, { 0, 5 });
            }));

        res = gaussLegendreIntegralSplit(0, 2, f, 4, 10);
        integration.AddTest("Gauss-Legendre - Correct input", std::abs(res - (8.0 / 3.0)) < tol);
        integration.AddTest("Gauss-Legendre - Incorrect quadrature rule", shouldThrowException([&]() {
			gaussLegendreIntegralSplit(0, 2, f, -1, 20);
			}));
    }

    {
		UnitGroup approximation("Approximation");
		
        auto f = [](double x) { return std::sin(x); };

        Approximation<decltype(f)> approx(f, 2, { 0.0, 2.0 });
		approximation.AddTest("Approximation - Correct input", std::abs(approx.Approximate(1.0) - std::sin(1.0)) < tol);
    
        approximation.AddTest("Approximation - reversed range", shouldThrowException([&]() {
            Approximation<decltype(f)> bad(f, 2, { 2.0, 0.0 });
            }));

		approximation.AddTest("Approximation - negative degree", shouldThrowException([&]() {
			Approximation<decltype(f)> bad(f, -1, { 0.0, 2.0 });
			}));
    }

    {
        UnitGroup ode("Ordinary Differential Equations");
        auto f = [](double x, double y) { return x + y; };

        std::vector<double> res = ode::eulerMethod(0.0, f, 0.0, 1.0, 1000);
        ode.AddTest("Euler - Correct input", std::abs(res.back() - 0.718281828459045) < tol);
        ode.AddTest("Euler - Invalid range", shouldThrowException([&]() {
            ode::eulerMethod(0.0, f, 1.0, 0.0, 1);
			}));
        res = ode::heunMethod(0.0, f, 0.0, 1.0, 1000);
        ode.AddTest("Heun - Correct input", std::abs(res.back() - 0.718281828459045) < tol);
        ode.AddTest("Heun - Zero step size", shouldThrowException([&]() {
            ode::heunMethod(0.0, f, 1.0, 1.0, 1);
            }));
        res = ode::midpointMethod(0.0, f, 0.0, 1.0, 1000);
        ode.AddTest("Midpoint - Correct input", std::abs(res.back() - 0.718281828459045) < tol);
        ode.AddTest("Midpoint - Invalid range", shouldThrowException([&]() {
			ode::midpointMethod(0.0, f, 1.0, 0.0, 1);
			}));
        res = ode::midpointMethod(0, f, 0, 1, 10);

        res = ode::rungeKutta4Method(0, f, 0, 1, 10);
		ode.AddTest("Runge-Kutta - Correct input", std::abs(res.back() - 0.718281828459045) < tol);
        ode.AddTest("Runge-Kutta - Zero step size", shouldThrowException([&]() {
            ode::rungeKutta4Method(0, f, 1, 1, 1);
            }));
    }
}
