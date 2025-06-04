#include "approximation.hpp"


template <typename Func>
class Approximation
{
    Func function;
    vector<double> coeffs;
    int degree;
    vector<double> range;

public:
    Approximation(Func func, int deg, vector<double> r) : function(func), degree(deg), range(r)
    {
        coeffs.resize(degree + 1);
        vector<vector<double>> A(degree + 1, vector<double>(degree + 1));
        vector<double> b(degree + 1);

        // macierz A - analitycznie
        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= degree; j++) {
                int power = i + j;
                A[i][j] = (pow(range[1], power + 1) - pow(range[0], power + 1)) / (power + 1);
            }
        }

        // wektor B - Gauss-Legendre
        for (int i = 0; i <= degree; i++) {
            b[i] = gaussLegendreIntegralSplit(range[0], range[1], [this, i](double x) { return this->function(x) * pow(x, i); }, 4, 10);
        }

        coeffs = GaussElimination(A, b);
    }

    double Approximate(double x)
    {
        double result = 0.0;
        for (int i = 0; i < coeffs.size(); i++)
        {
            result += coeffs[i] * pow(x, i);
        }
        return result;
    }

    double operator()(double x)
    {
        return Approximate(x);
    }

    void PrintCoeffs()
    {
        cout << "Wspolczynniki wielomianu:\n";
        for (int i = 0; i < coeffs.size(); i++)
        {
            cout << "a[" << i << "] = " << coeffs[i] << "\n";
        }
    }
};