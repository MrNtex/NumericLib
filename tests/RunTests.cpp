#include "Test.h"
#include "interpolation/newton.hpp"
#include "interpolation/lagrange.hpp"
#include "nonliniear.hpp"

#define tol 0.01

using namespace std;

double testFunc(double x)
{
    return pow(x, 2) - 1;
}

void RunTests()
{
    // Lagrande Interpolation

    vector<double> x = { 1, 2, 3 };
    vector<double> y = { 2, 3, 5 };

    double res = Interpolate(2.5, x, y, 1);

    UnitTest lagrandeInterpolation("Lagrande Interpolation", res - 3.875 < tol);

	// Newton Interpolation

    x = { 1, 2, 3 };
    y = { 2, 3, 5 };

    res = interpolate(2.5, x, y);

    UnitTest newtonInterpolation("Newton Interpolation", res - 3.875 < tol);

    vector<UnitTest> tests = { lagrandeInterpolation, newtonInterpolation };

    UnitGroup iterpolations("Interpolations:", tests);

    /// NONLINIEAR EQUASIONS

    vector<double> dummy;

    res = bisection(testFunc, 0.5, 1.5, dummy);


}