#pragma once
#include <vector>
#include <iomanip>
#include <numeric>

using namespace std;

void pivot(vector<vector<double>>& A, vector<double>& b, int k);

void luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L,
    vector<vector<double>>& U, vector<double>& b);

vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b);

vector<double> backwardSubstitution(const vector<vector<double>>& U, const vector<double>& z);

vector<double> solveWithFullPivotLU(vector<vector<double>> A, vector<double> b);
