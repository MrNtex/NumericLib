#include "integration/rectangle.hpp"

double Rect(double step, double (*func)(double), std::vector<double>& range)
{
    double h = (range[1] - range[0]) / step;
    double i = range[0];

    double sum = 0;

    while (i < range[1])
    {
        sum += func(i) * h;
        i += h;
    }

    return sum;
}