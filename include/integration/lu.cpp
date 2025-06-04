#include "liniear_systems/lu.hpp"
#include <stdexcept>


void pivot(vector<vector<double>>& A, vector<double>& b, int k) {
    int n = A.size();
    int maxRow = k;
    for (int i = k + 1; i < n; i++) {
        if (abs(A[i][k]) > abs(A[maxRow][k])) {
            maxRow = i;
        }
    }
    if (maxRow != k) {
        swap(A[k], A[maxRow]);
        swap(b[k], b[maxRow]);
    }
}


void luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, vector<double>& b) {
    int n = A.size();

    L.resize(n, vector<double>(n));
    U.resize(n, vector<double>(n));

    for (int i = 0; i < n; i++) {

        for (int j = i; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }
        for (int j = i; j < n; j++) {
            if (i == j)
                L[i][i] = 1;
            else {
                double sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += L[j][k] * U[k][i];
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }

        //cout << "Macierze po iteracji: " << i << ": " << endl;
        //PrintMatrix(L);
        //PrintMatrix(U);

    }
}


vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b) {
    int n = L.size();
    vector<double> z(n, 0);
    for (int i = 0; i < n; i++) {
        z[i] = b[i];
        for (int j = 0; j < i; j++) {
            z[i] -= L[i][j] * z[j];
        }
        z[i] /= L[i][i];
    }
    return z;
}

vector<double> backwardSubstitution(const vector<vector<double>>& U, const vector<double>& z) {
    int n = U.size();
    vector<double> x(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = z[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
    return x;
}

vector<double> solveWithFullPivotLU(vector<vector<double>> A, vector<double> b) {
    const int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U = A;
    vector<int> row_perm(n), col_perm(n);

    iota(row_perm.begin(), row_perm.end(), 0);
    iota(col_perm.begin(), col_perm.end(), 0);

    for (int k = 0; k < n; ++k) {
        // Znajdz pivot
        double max_val = 0;
        int max_row = k, max_col = k;
        for (int i = k; i < n; ++i) {
            for (int j = k; j < n; ++j) {
                if (fabs(U[i][j]) > max_val) {
                    max_val = fabs(U[i][j]);
                    max_row = i;
                    max_col = j;
                }
            }
        }

        if (max_val == 0) throw runtime_error("Macierz jest osobliwa");

        // Zamiana wierszy
        if (max_row != k) {
            swap(U[k], U[max_row]);
            swap(b[k], b[max_row]);
            swap(row_perm[k], row_perm[max_row]);

            for (int j = 0; j < k; ++j) {
                swap(L[k][j], L[max_row][j]);
            }
        }

        // Zamiana kolumn
        if (max_col != k) {
            for (int i = 0; i < n; ++i) {
                swap(U[i][k], U[i][max_col]);
            }
            swap(col_perm[k], col_perm[max_col]);

            for (int i = 0; i < n; ++i) {
                swap(L[i][k], L[i][max_col]);
            }
        }

        L[k][k] = 1.0;
        for (int i = k + 1; i < n; ++i) {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < n; ++j) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }

    vector<double> z = forwardSubstitution(L, b);
    vector<double> x = backwardSubstitution(U, z);

    // Przywrocenie kolejnosci kolumn
    vector<double> final_x(n);
    for (int i = 0; i < n; ++i) {
        final_x[col_perm[i]] = x[i];
    }

    return final_x;
}
