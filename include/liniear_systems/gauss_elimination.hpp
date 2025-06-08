#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace NumericLib {
	/// <summary>
	/// solves a system of linear equations using Gaussian elimination method with partial pivoting
	/// </summary>
	/// <param name="A">
	/// vector reference to A (n x n) matrix representing the coefficients of the system of equations
	/// </param>
	/// <param name="b">
	/// vector reference to a vector of size n representing the right-hand side of the system of equations
	/// </param>
	/// <returns>
	/// vector of size n containing the solution to the system of equations, where n is the number of equations in the system
	/// </returns>
	/// <exception cref="std::runtime_error">
	/// thrown if the system of equations is linearly dependent so that there is no unique solution.
	/// </exception>
	std::vector<double> GaussElimination(std::vector<std::vector<double>>& A, std::vector<double>& b);

} // namespace NumericLib
