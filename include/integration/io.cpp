#include "numeric_io.hpp"

bool is_number(char c) {
    return (c >= '0' && c <= '9') || c == '-' || c == '.';
}

void ConvertLine(const string& line, vector<double>& target) {
    string buffor;
    for (int i = 0; i < line.length(); i++) {
        while (i < line.length() && is_number(line[i])) {
            buffor += line[i];
            i++;
        }
        if (!buffor.empty()) {
            target.push_back(stod(buffor));
            buffor.clear();
        }
    }
}

void LoadMatrix(const string& source, vector<vector<double>>& A, vector<double>& B)
{
    ifstream file(source);
    if (!file.is_open()) {
        cerr << "Blad! Nie mozna otworzyc pliku." << endl;
        return;
    }

    string line;

    // Pierwsza linia
    getline(file, line);

    vector<double> nbuffor;

    // xi
    getline(file, line);
    ConvertLine(line, nbuffor);

    int n = (int)nbuffor[0];

    A.resize(n, vector<double>(n));

    getline(file, line); // b:

    getline(file, line);
    ConvertLine(line, B);

    getline(file, line); // A:
    for (int i = 0; i < n; i++)
    {
        vector<double> lineBuffor;
        getline(file, line);

        ConvertLine(line, lineBuffor);

        A[i] = lineBuffor;
    }

    file.close();
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
