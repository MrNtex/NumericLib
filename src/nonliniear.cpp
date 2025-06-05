#include "nonliniear.hpp"

#include <vector>
#include <cmath>

namespace NumericLib {

template<typename Func>
double bisection(Func f, double a, double b, std::vector<double>& iter, double tol, int max_iter) {
    if (f(a) * f(b) >= 0) throw std::invalid_argument("Brak przeciecia osi OX.");

    double c;
    for (int i = 0; i < max_iter; ++i) {
        c = (a + b) / 2;
        iter.push_back(c);
        double fc = f(c);
        if (std::abs(fc) < tol || (b - a) / 2 < tol) return c;

        (f(a) * fc < 0) ? b = c : a = c;
    }
    return c;
}

template<typename Func, typename Derivative>
double newton(Func f, double x0, Derivative df, std::vector<double>& iter, double tol, int max_iter) {
    for (int i = 0; i < max_iter; ++i) {
        iter.push_back(x0);
        double fx = f(x0);
        if (std::abs(fx) < tol) return x0;

        double dfx = df(x0);
        if (std::abs(dfx) < std::numeric_limits<double>::epsilon()) throw std::runtime_error("Pochodna = 0.");

        x0 -= fx / dfx;
    }
    return x0;
}

template<typename Func>
double newton_numeric(Func f, double x0, std::vector<double>& iter, double tol, int max_iter) {
    auto numerical_derivative = [f](double x) {
        double h = 1e-5;
        return (f(x + h) - f(x - h)) / (2 * h);
        };
    return newton(f, x0, numerical_derivative, iter, tol, max_iter);
}

template<typename Func>
double secant(Func f, double x0, double x1, std::vector<double>& iter, double a, double b, double tol, int max_iter) {
    double fx0 = f(x0), fx1 = f(x1);

    for (int i = 0; i < max_iter; ++i) {
        if (std::abs(fx1) < tol) {
            iter.push_back(x1);
            return x1;
        }

        if (std::abs(fx1 - fx0) < std::numeric_limits<double>::epsilon()) {
            throw std::runtime_error("Dzielenie przez 0 w metodzie siecznych.");
        }

        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

        if (x2 < a) x2 = a;
        else if (x2 > b) x2 = b;

        iter.push_back(x2);

        if (std::abs(x2 - x1) < tol) return x2;

        x0 = x1;
        fx0 = fx1;
        x1 = x2;
        fx1 = f(x1);
    }

    return x1;
}

template<typename Func>
double falsi(Func f, double a, double b, std::vector<double>& iter, double tol, int max_iter) {
    double fa = f(a), fb = f(b);

    if (fa * fb >= 0) throw std::invalid_argument("Brak przeciecia osi OX.");

    double c = a;

    for (int i = 0; i < max_iter; ++i) {
        c = (a * fb - b * fa) / (fb - fa);
        double fc = f(c);
        iter.push_back(c);

        if (std::abs(fc) < tol) return c;

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
        if (std::abs(b - a) < tol) break;
    }

    return c;
}

template<typename Func>
std::vector<std::pair<double, double>> find_intervals(Func f, double a, double b, double step) {
    std::vector<std::pair<double, double>> intervals;

    for (double x = a; x < b; x += step) {
        try {
            double fx = f(x);
            double fx_step = f(x + step);
            if (fx * fx_step < 0) {
                intervals.emplace_back(x, x + step);
            }
        }
        catch (const std::exception& e) {
            // Skip invalid points
        }
    }
    return intervals;
}

} // namespace NumericLib