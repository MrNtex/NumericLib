#include "nonliniear.hpp"

#include <vector>
#include <cmath>

using namespace std;

template<typename Func>
double bisection(Func f, double a, double b, vector<double>& iter, double tol, int max_iter) {
    if (f(a) * f(b) >= 0) throw invalid_argument("Brak przeciecia osi OX.");

    double c;
    for (int i = 0; i < max_iter; ++i) {
        c = (a + b) / 2;
        iter.push_back(c);
        double fc = f(c);
        if (abs(fc) < tol || (b - a) / 2 < tol) return c;

        (f(a) * fc < 0) ? b = c : a = c;
    }
    return c;
}

template<typename Func, typename Derivative>
double newton(Func f, double x0, Derivative df, vector<double>& iter, double tol, int max_iter) {
    for (int i = 0; i < max_iter; ++i) {
        iter.push_back(x0);
        double fx = f(x0);
        if (abs(fx) < tol) return x0;

        double dfx = df(x0);
        if (abs(dfx) < numeric_limits<double>::epsilon()) throw runtime_error("Pochodna = 0.");

        x0 -= fx / dfx;
    }
    return x0;
}

template<typename Func>
double newton_numeric(Func f, double x0, vector<double>& iter, double tol, int max_iter) {
    auto numerical_derivative = [f](double x) {
        double h = 1e-5;
        return (f(x + h) - f(x - h)) / (2 * h);
        };
    return newton(f, x0, numerical_derivative, iter, tol, max_iter);
}
template<typename Func>
double secant(Func f, double x0, double x1, vector<double>& iter, double a, double b, double tol, int max_iter) {
    double fx0 = f(x0), fx1 = f(x1);

    for (int i = 0; i < max_iter; ++i) {
        if (abs(fx1) < tol) {
            iter.push_back(x1);
            return x1;
        }

        if (abs(fx1 - fx0) < numeric_limits<double>::epsilon()) {
            throw runtime_error("Dzielenie przez 0 w metodzie siecznych.");
        }

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

        if (x2 < a) x2 = a;
        else if (x2 > b) x2 = b;

        iter.push_back(x2);

        if (abs(x2 - x1) < tol) return x2;

        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = f(x1);
    }

    return x1;
}

template<typename Func>
double falsi(Func f, double a, double b, vector<double>& iter, double tol, int max_iter) {
    double fa = f(a), fb = f(b);

    if (fa * fb >= 0) throw invalid_argument("Brak przeciecia osi OX.");

    double c = a;

    for (int i = 0; i < max_iter; ++i) {
        c = (a * fb - b * fa) / (fb - fa);
        double fc = f(c);
        iter.push_back(c);

        //cout << "x: " << c << ", f(x): " << fc << "\n";

        if (abs(fc) < tol) return c;

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
        if (abs(b - a) < tol) break;
    }

    return c;
}



template<typename Func>
vector<pair<double, double>> find_intervals(Func f, double a, double b, double step) {
    vector<pair<double, double>> intervals;

    for (double x = a; x < b; x += step) {

        try {
            double fx = f(x);
            double fx_step = f(x + step);
            if (fx * fx_step < 0) {
                intervals.emplace_back(x, x + step);
            }
        }
        catch (const exception& e) {
            //cerr << "Blad dla x=" << x << ": " << e.what() << "\n";
        }

    }
    return intervals;
}