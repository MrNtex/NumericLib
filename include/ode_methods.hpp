#pragma once
#include <vector>

using namespace std;

template<typename Func>
vector<double> eulerMethod(double y0, Func f, double a, double b, int N) {
    vector<double> results;
    double y = y0, t = a, h = (b - a) / N;
    for (int i = 0; i <= N; ++i) {
        results.push_back(y);
        y += h * f(t, y);
        t += h;
    }
    return results;
}

template<typename Func>
vector<double> heunMethod(double y0, Func f, double a, double b, int N) {
    vector<double> results;
    double y = y0, t = a, h = (b - a) / N;
    for (int i = 0; i <= N; ++i) {
        results.push_back(y);
        double k1 = f(t, y);
        double k2 = f(t + h, y + h * k1);
        y += h * 0.5 * (k1 + k2);
        t += h;
    }
    return results;
}

template<typename Func>
vector<double> midpointMethod(double y0, Func f, double a, double b, int N) {
    vector<double> results;
    double y = y0, t = a, h = (b - a) / N;
    for (int i = 0; i <= N; ++i) {
        results.push_back(y);
        double k1 = f(t, y);
        double k2 = f(t + h / 2, y + h / 2 * k1);
        y += h * k2;
        t += h;
    }
    return results;
}

template<typename Func>
vector<double> rungeKutta4Method(double y0, Func f, double a, double b, int N) {
    vector<double> results;
    double y = y0, t = a, h = (b - a) / N;
    for (int i = 0; i <= N; ++i) {
        results.push_back(y);
        double k1 = f(t, y);
        double k2 = f(t + h / 2, y + h / 2 * k1);
        double k3 = f(t + h / 2, y + h / 2 * k2);
        double k4 = f(t + h, y + h * k3);
        y += h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        t += h;
    }
    return results;
}