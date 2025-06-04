#include "interpolation/lagrange.hpp"

double Interpolate(double x, const vector<double>& xi, const vector<double>& fxi, int prec)
{
    double sum = 0;

    for (int i = 0; i < xi.size(); i += prec)
    {
        double y = fxi[i];
        double pi = 1;

        for (int j = 0; j < fxi.size(); j += prec)
        {
            if (i == j) continue;
            double frac = (x - xi[j]) / (xi[i] - xi[j]);

            pi *= frac;
        }

        sum += pi * y;
    }

    return sum;
}
