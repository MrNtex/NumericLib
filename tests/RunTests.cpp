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
        interpolation.AddTest("Correct input", std::abs(res - 3.875) < tol);

        std::vector<double> badX = { 1, 2 };
        std::vector<double> badY = { 2, 3, 4 };
        interpolation.AddTest("Mismatched sizes", shouldThrowException([&]() {
            InterpolateLagrange(2.0, badX, badY, 1);
            }));

        x = { 1, 2, 3 };
        y = { 2, 3, 5 };

        res = InterpolateNewton(2.5, x, y);
        interpolation.AddTest("Correct input", std::abs(res - 3.875) < tol);

        interpolation.AddTest("Empty input", shouldThrowException([&]() {
            InterpolateNewton(2.0, {}, {});
            }));
    }

    /*{
        UnitGroup nonliniear("Nonliniear Methods");

        std::vector<double> dummy;
        double res = bisection(testFunc, 0.0, 2.0, dummy);
        nonliniear.AddTest("Correct input", std::abs(res - 1.0) < tol);

        nonliniear.AddTest("No sign change", shouldThrowException([&]() {
            bisection(testFunc, 2.0, 3.0, dummy);
            }));
    }*/
}
