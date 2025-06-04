#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <numeric>

using namespace std;

bool is_number(char c);
void ConvertLine(const string& line, vector<double>& target);
void LoadMatrix(const string& source, vector<vector<double>>& A, vector<double>& B);
void PrintMatrix(vector<vector<double>>& A);
void PrintMatrix(vector<vector<double>>& A, vector<double>& b);