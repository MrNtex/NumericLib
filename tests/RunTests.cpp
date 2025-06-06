#include "Test.h"
#include "NumericLib.hpp"

#define tol 0.01
using namespace NumericLib;

double testFunc(double x) {
    return x * x - 1;
}

void RunTests() {
    {
        UnitGroup interpolation("Interpolation");

        std::vector<double> x = { 1, 2, 3 };
        std::vector<double> y = { 2, 3, 5 };

        double res = InterpolateLagrange(2.5, x, y, 1);
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

		res = Simpson(100, f, { 0.0, 2.0 });
		integration.AddTest("Simpson - Correct input", std::abs(res - (8.0 / 3.0)) < tol);

		res = Rect(10000, f, { 0.0, 2.0 });
		integration.AddTest("Rectangle - Correct input", std::abs(res - (8.0 / 3.0)) < tol);

		res = gaussLegendreIntegralSplit(0, 2, f, 4, 10);
		integration.AddTest("Gauss-Legendre - Correct input", std::abs(res - (8.0 / 3.0)) < tol);
	}
}
