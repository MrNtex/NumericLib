#pragma once

#include <string>
#include <vector>

namespace NumericLib {

void print_iterations(const std::string& name, const std::vector<double>& values, double root) {
    std::cout << "\nPrzyblizenia (" << name << ") [|x_n - x*|]:\n";
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << "Iteracja " << i + 1 << ": " << std::setw(12) << values[i]
            << "  Blad: " << std::abs(values[i] - root) << "\n";
    }
}

double GetValueHorner(double x, std::vector<double>& ai, int n = 3) {
    double value = 0;
    for (int i = n; i >= 0; i--) {
        value = value * x + ai[i];
    }
    return value;
}

void PrintMatrix(vector<vector<double>>& A)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(10) << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void PrintMatrix(vector<vector<double>>& A, vector<double>& b)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(10) << A[i][j] << " ";
        }

        cout << "| " << b[i] << endl;
    }
    cout << endl;
}

bool VerifyMatrix(vector<vector<double>>& A, vector<double>& b, vector<double>& x)
{
    int n = A.size();


    for (int i = 0; i < n; i++)
    {
        double sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += x[j] * A[i][j];
        }

        if (abs(sum - b[i]) > 1e-5) return false;
    }

    return true;
}

} // namespace NumericLib