#include "liniear_systems/gauss_elimination.hpp"
using namespace std;


vector<double> GaussElimination(vector<vector<double>>& A, vector<double>& b)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
        {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        if (A[maxRow][i] == 0)
        {
            cout << "Uklad rownan jest liniowo zalezny (brak unikalnego rozwiazania)." << endl;
            //throw runtime_error("Uklad rownan jest liniowo zalezny (brak unikalnego rozwiazania).");
            exit(1);
        }

        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

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

    vector<double> x(n);

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