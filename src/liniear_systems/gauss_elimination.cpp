#include "liniear_systems/gauss_elimination.hpp"

namespace NumericLib {

std::vector<double> GaussElimination(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
        {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        if (A[maxRow][i] == 0)
        {
            throw std::runtime_error("The system of equations is linearly dependent (no unique solution).");
        }

        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);

        // Eliminacja
        for (int j = i + 1; j < n; j++)
        {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
        {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

} // namespace NumericLib