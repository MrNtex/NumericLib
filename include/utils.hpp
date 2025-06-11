#pragma once

#include <string>
#include <vector>

namespace NumericLib {
    /// <summary>
	/// Prints the iterations of a numerical method with the name and values.
	/// </summary>
	/// <param name="name">Name of the method.</param>
	/// <param name="values">Vector of values to print.</param>
	/// <param name="root">The root value for comparison.</param>
	void print_iterations(const std::string& name, const std::vector<double>& values, double root);
	/// <summary>
	/// Evaluates a polynomial using Horner's method.
	/// </summary>
	/// <param name="x">The point at which to evaluate the polynomial.</param>
	/// <param name="ai">Coefficients of the polynomial, where ai[i] is the coefficient for x^i.</param>
	/// <param name="n">Degree of the polynomial (number of coefficients - 1).</param>
	/// <returns>The value of the polynomial at point x.</returns>
	double GetValueHorner(double x, std::vector<double>& ai, int n = 3);
	/// <summary>
	/// Prints a matrix to the standard output.
	/// </summary>
	/// <param name="A">The matrix to print.</param>
	/// <param name="b">Optional vector b to print alongside the matrix.</param>
	/// <returns>void</returns>
	void PrintMatrix(std::vector<std::vector<double>>& A);
	/// <summary>
	/// Prints a matrix to the standard output.
	/// </summary>
	/// <param name="A">The matrix to print.</param>
	/// <param name="b">Optional vector b to print alongside the matrix.</param>
	/// <returns>void</returns>
	void PrintMatrix(std::vector<std::vector<double>>& A, std::vector<double>& b);
	/// <summary>
	/// Verifies if the solution x satisfies the equation Ax = b.
	/// </summary>
	/// <param name="A">The matrix A.</param>
	/// <param name="b">The vector b.</param>
	/// <param name="x">The solution vector x.</param>
	/// <returns>True if the solution is valid, false otherwise.</returns>
	bool VerifyMatrix(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x);

} // namespace NumericLib