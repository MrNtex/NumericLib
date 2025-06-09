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

/// <summary>
/// checks if a character is a digit, a minus sign or a dot
/// </summary>
/// <param name="c">
/// character to check
/// </param>
/// <returns>
/// true if the character is a digit, a minus sign or a dot, false otherwise
/// </returns>
bool is_number(char c);

/// <summary>
/// extracts numbers from a line of text and converts them to doubles
/// </summary>
/// <param name="line">
/// input string line containing numbers to be converted
/// </param>
/// <param name="target">
/// output vector to store the converted numbers
/// </param>
void ConvertLine(const string& line, vector<double>& target);

/// <summary>
/// loads matrix A and vector B from a file
/// </summary>
/// <param name="source">
/// path to the file containing the matrix and vector data
/// </param>
/// <param name="A">
/// matrix A to be filled with the data from the file
/// </param>
/// <param name="B">
/// matrix B to be filled with the data from the file
/// </param>
void LoadMatrix(const string& source, vector<vector<double>>& A, vector<double>& B);

/// <summary>
/// prints the matrix A to the console
/// </summary>
/// <param name="A">
/// 
/// </param>
void PrintMatrix(vector<vector<double>>& A);
void PrintMatrix(vector<vector<double>>& A, vector<double>& b);