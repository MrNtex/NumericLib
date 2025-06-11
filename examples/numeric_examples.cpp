#include<iostream>
#include<NumericLib.hpp>
#include <cmath>

#define M_PI 3.14159265358979323846

using namespace NumericLib;

int RunExamples()
{
	//#1
	//Example of using methods for calculating integrals: rectangle, trapezoids, simpson and gauss-legendre 

	std::cout << "Integration methods example:\n\n";

	//Range of integration
	std::vector<double> range = { 0.0, M_PI};

	//Function to integrate
	auto funcIntegration = [](double x) { return sin(3*x); };

	//Number of steps 
	int steps = 1000;

	//Number of nodes for Gauss-Legendre method
	int gaussNodes = 4;

	//Calculating integrals using different methods
	double rectResult = Rect(steps, funcIntegration, range);
	double simpsonResult = Simpson(steps, funcIntegration, range);
	double trapezoidResult = Trapezoids(steps, funcIntegration, range);
	double gaussResult = gaussLegendreIntegralSplit(range[0], range[1], funcIntegration, gaussNodes, steps);

	//output results
	std::cout << "Rectangle method result: " << rectResult << std::endl;
	std::cout << "Simpson's method result: " << simpsonResult << std::endl;
	std::cout << "Trapezoid method result: " << trapezoidResult << std::endl;
	std::cout << "Gauss-Legendre method result: " << gaussResult << std::endl << std::endl;

	//#2
	//Example of using Lagrange and Newton interpolation methods

	std::cout << "Interpolation methods example:\n\n";

	//Function definition
	auto funcInterpolation = [](double x) {
		return std::exp(-x) * std::sin(3 * x);
	};

	//Interpolation nodes
	std::vector<double> xi = { 0.8, 0.9, 1.0, 1.1, 1.2 };

	std::vector<double> fxi;
	for (double x : xi) {
		fxi.push_back(funcInterpolation(x));
	}

	//Interpolation point
	double x = 1.1;

	double lagrangeResult = InterpolateLagrange(x, xi, fxi, xi.size());
	double newtonResult = InterpolateNewton(x, xi, fxi);

	//output results
	std::cout << "Lagrange interpolation result at x = " << x << ": " << lagrangeResult << std::endl;
	std::cout << "Newton interpolation result at x = " << x << ": " << newtonResult << std::endl << std::endl;

	//#3
	//Example of using gauss-elimination method to solve a system of linear equations

	std::cout << "Gauss Elimination method example:\n\n";

	//Matrix A definition

	std::vector<std::vector<double>> A = {
		{2, 3, -1},
		{4, 1, 2},
		{-2, 5, -3}
	};

	//vector b definition
	std::vector<double> b = { 5, 6, -4 };

	//x vector to store the solution
	std::vector<double> x_gl = NumericLib::GaussElimination(A, b);

	//solving linear equations
	for (size_t i = 0; i < x_gl.size(); ++i) {
		std::cout << "x" << i + 1 << " = " << x_gl[i] << '\n';
	}

	std::cout << std::endl;

	//#4
	//Example of using approximation methods to approximate a function using polynomial approximation
	
	std::cout << "\nApproximation methods example:\n\n";

	//Function to approximate
	auto funcApprox = [](double x) {
		return std::exp(-x) * std::sin(3 * x);
	};

	//Range of approximation
	std::vector<double> rangeApprox = { 0.0, M_PI };

	//Degree of polynomial approximation
	NumericLib::Approximation<decltype(funcApprox)> approx(funcApprox, 3, rangeApprox);

	//Print coefficients of the approximating polynomial
	approx.PrintCoeffs();

	std::cout << std::endl;

	//checking the approximation at a points
	for (double x = 0.0; x <= M_PI; x += M_PI / 6) {
		double real = funcApprox(x);
		double approxVal = approx(x);
		std::cout << "x = " << x << ", f(x) = " << real << ", approx(x) = " << approxVal << '\n';
	}

	return 0;
}