#pragma once

#include <string>
#include <vector>

namespace NumericLib {

	void print_iterations(const std::string& name, const std::vector<double>& values, double root);
	double GetValueHorner(double x, std::vector<double>& ai, int n = 3);
	void PrintMatrix(std::vector<std::vector<double>>& A);
	void PrintMatrix(std::vector<std::vector<double>>& A, std::vector<double>& b);
	bool VerifyMatrix(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& x);

} // namespace NumericLib