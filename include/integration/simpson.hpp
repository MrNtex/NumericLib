#pragma once
#include <vector>

using namespace std;
double Simpson(int split, double (*func)(double), const vector<double>& range);
