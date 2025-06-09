#pragma once
#include <vector>
#include <iomanip>
#include <numeric>

namespace NumericLib {

    /// <summary>
	/// performs partial pivoting on the matrix A and vector b at the k-th step by swapping rows
    /// </summary>
    /// <param name="A">
	/// matrix A (n x n) representing the coefficients of the system of equations
    /// </param>
    /// <param name="b">
	/// right-hand side vector b of size n representing the constants of the system of equations
    /// </param>
    /// <param name="k">
	/// current step of the elimination process
    /// </param>
    void pivot(std::vector<std::vector<double>>& A, std::vector<double>& b, int k);

    /// <summary>
	/// performs LU decomposition of matrix A into lower triangular matrix L and upper triangular matrix U
    /// </summary>
    /// <param name="A">
	/// not modified matrix A (n x n) to be decomposed
    /// </param>
    /// <param name="L">
	/// lower triangular matrix L (n x n) to be filled with the decomposition result
    /// </param>
    /// <param name="U">
	/// upper triangular matrix U (n x n) to be filled with the decomposition result
    /// </param>
    /// <param name="b">
	/// right-hand side vector b of size n representing the constants of the system of equations
    /// </param>
    void luDecomposition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L,
        std::vector<std::vector<double>>& U, std::vector<double>& b);

    /// <summary>
	/// solves the lower triangular system Lz = b using forward substitution
    /// </summary>
    /// <param name="L">
	/// lower triangular matrix L (n x n)
    /// </param>
    /// <param name="b">
	/// right-hand side vector b of size n representing the constants of the system of equations
    /// </param>
    /// <returns>
	/// vector z of size n containing the solution to the system Lz = b
    /// </returns>
    std::vector<double> forwardSubstitution(const std::vector<std::vector<double>>& L, const std::vector<double>& b);

    /// <summary>
	/// solves the upper triangular system Ux = z using backward substitution
    /// </summary>
    /// <param name="U">
	/// upper triangular matrix U (n x n)
    /// </param>
    /// <param name="z">
	/// right-hand side vector z of size n representing the constants of the system of equations
    /// </param>
    /// <returns>
	/// vector x of size n containing the solution to the system Ux = z
    /// </returns>
    std::vector<double> backwardSubstitution(const std::vector<std::vector<double>>& U, const std::vector<double>& z);

    /// <summary>
	/// solves a system of linear equations using LU decomposition with full pivoting
    /// </summary>
    /// <param name="A">
	/// matrix A (n x n) representing the coefficients of the system of equations
    /// </param>
    /// <param name="b">
	/// right-hand side vector b of size n representing the constants of the system of equations
    /// </param>
    /// <returns>
	/// solution vector x for the system of equations Ax = b, where n is the number of equations
    /// </returns>
	/// <exception cref="std::runtime_error">
	/// thrown if the matrix A is singular, meaning it does not have an inverse and the system of equations does not have a unique solution
    /// </exception>
    std::vector<double> solveWithFullPivotLU(std::vector<std::vector<double>> A, std::vector<double> b);

} // namespace NumericLib
