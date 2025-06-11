#include <vector>
#include <cmath>

namespace NumericLib {

    /// <summary>
    /// Finds a root of the function f in the interval [a, b] using the bisection method.
    /// Throws if f(a) and f(b) do not have opposite signs.
    /// </summary>
    /// <typeparam name="Func">Callable type representing the function f.</typeparam>
    /// <param name="f">Function to find root for.</param>
    /// <param name="a">Left endpoint of the interval.</param>
    /// <param name="b">Right endpoint of the interval.</param>
    /// <param name="iter">Vector to store intermediate root approximations.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum number of iterations (default 1000).</param>
    /// <returns>Approximate root of f in [a, b].</returns>
    template<typename Func>
    double bisection(Func f, double a, double b, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000) {
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

    /// <summary>
    /// Finds a root of the function f in the interval [a, b] using the bisection method.
    /// Throws if f(a) and f(b) do not have opposite signs or if root not found in max iterations.
    /// </summary>
    /// <typeparam name="Func">Callable type representing the function f.</typeparam>
    /// <param name="f">Function to find root for.</param>
    /// <param name="a">Left endpoint of the interval.</param>
    /// <param name="b">Right endpoint of the interval.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum number of iterations (default 1000).</param>
    /// <returns>Approximate root of f in [a, b].</returns>
    template<typename Func>
    double bisection(Func f, double a, double b, double tol = 1e-8, int max_iter = 1000) {
        if (f(a) * f(b) >= 0) throw std::invalid_argument("Brak przeciecia osi OX.");

        double c;
        for (int i = 0; i < max_iter; ++i) {
            c = (a + b) / 2;
            double fc = f(c);
            if (std::abs(fc) < tol || (b - a) / 2 < tol) return c;

            (f(a) * fc < 0) ? b = c : a = c;
        }
        throw std::runtime_error("Nie znaleziono pierwiastka w zadanej liczbie iteracji.");
    }

    /// <summary>
    /// Finds a root of the function f using Newton's method starting from x0.
    /// Uses the derivative df and stores iteration approximations in iter.
    /// </summary>
    /// <typeparam name="Func">Callable type for function f.</typeparam>
    /// <typeparam name="Derivative">Callable type for derivative df.</typeparam>
    /// <param name="f">Function whose root to find.</param>
    /// <param name="x0">Initial guess for the root.</param>
    /// <param name="df">Derivative of f.</param>
    /// <param name="iter">Vector to store intermediate approximations.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum iterations (default 1000).</param>
    /// <returns>Approximate root of f.</returns>
    template<typename Func, typename Derivative>
    double newton(Func f, double x0, Derivative df, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000) {
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

    /// <summary>
    /// Finds a root of the function f using Newton's method starting from x0.
    /// Uses the derivative df.
    /// </summary>
    /// <typeparam name="Func">Callable type for function f.</typeparam>
    /// <typeparam name="Derivative">Callable type for derivative df.</typeparam>
    /// <param name="f">Function whose root to find.</param>
    /// <param name="x0">Initial guess for the root.</param>
    /// <param name="df">Derivative of f.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum iterations (default 1000).</param>
    /// <returns>Approximate root of f.</returns>
    template<typename Func, typename Derivative>
    double newton(Func f, double x0, Derivative df, double tol = 1e-8, int max_iter = 1000) {
        for (int i = 0; i < max_iter; ++i) {
            double fx = f(x0);
            if (std::abs(fx) < tol) return x0;

            double dfx = df(x0);
            if (std::abs(dfx) < std::numeric_limits<double>::epsilon()) throw std::runtime_error("Pochodna = 0.");

            x0 -= fx / dfx;
        }
        return x0;
    }

    /// <summary>
    /// Finds a root of the function f using Newton's method with numerical derivative approximation.
    /// Stores iteration approximations in iter.
    /// </summary>
    /// <typeparam name="Func">Callable type for function f.</typeparam>
    /// <param name="f">Function whose root to find.</param>
    /// <param name="x0">Initial guess for the root.</param>
    /// <param name="iter">Vector to store intermediate approximations.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum iterations (default 1000).</param>
    /// <returns>Approximate root of f.</returns>
    template<typename Func>
    double newton_numeric(Func f, double x0, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000) {
        auto numerical_derivative = [f](double x) {
            double h = 1e-5;
            return (f(x + h) - f(x - h)) / (2 * h);
            };
        return newton(f, x0, numerical_derivative, iter, tol, max_iter);
    }

    /// <summary>
    /// Finds a root of the function f using Newton's method with numerical derivative approximation (euler method).
    /// </summary>
    /// <typeparam name="Func">Callable type for function f.</typeparam>
    /// <param name="f">Function whose root to find.</param>
    /// <param name="x0">Initial guess for the root.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum iterations (default 1000).</param>
    /// <returns>Approximate root of f.</returns>
    template<typename Func>
    double newton_numeric(Func f, double x0, double tol = 1e-8, int max_iter = 1000) {
        auto numerical_derivative = [f](double x) {
            double h = 1e-5;
            return (f(x + h) - f(x - h)) / (2 * h);
            };
        return newton(f, x0, numerical_derivative, tol, max_iter);
    }

    /// <summary>
    /// Finds a root of the function f using the secant method starting with points x0 and x1,
    /// restricting the approximations within [a, b]. Stores iterations in iter.
    /// </summary>
    /// <typeparam name="Func">Callable type for function f.</typeparam>
    /// <param name="f">Function whose root to find.</param>
    /// <param name="x0">First initial guess.</param>
    /// <param name="x1">Second initial guess.</param>
    /// <param name="iter">Vector to store intermediate approximations.</param>
    /// <param name="a">Left boundary for approximations.</param>
    /// <param name="b">Right boundary for approximations.</param>
    /// <param name="tol">Tolerance for convergence (default 1e-8).</param>
    /// <param name="max_iter">Maximum iterations (default 1000).</param>
    /// <returns>Approximate root of f.</returns>
    template<typename Func>
    double secant(Func f, double x0, double x1, std::vector<double>& iter, double a, double b, double tol = 1e-8, int max_iter = 1000) {
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
    double secant(Func f, double x0, double x1, double a, double b, double tol = 1e-8, int max_iter = 1000) {
        double fx0 = f(x0), fx1 = f(x1);

        for (int i = 0; i < max_iter; ++i) {
            if (std::abs(fx1) < tol) {
                return x1;
            }

            if (std::abs(fx1 - fx0) < std::numeric_limits<double>::epsilon()) {
                throw std::runtime_error("Dzielenie przez 0 w metodzie siecznych.");
            }

            double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

            if (x2 < a) x2 = a;
            else if (x2 > b) x2 = b;

            if (std::abs(x2 - x1) < tol) return x2;

            x0 = x1;
            fx0 = fx1;
            x1 = x2;
            fx1 = f(x1);
        }

        return x1;
    }

    template<typename Func>
    double falsi(Func f, double a, double b, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000) {
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
    double falsi(Func f, double a, double b, double tol = 1e-8, int max_iter = 1000) {
        double fa = f(a), fb = f(b);

        if (fa * fb > 0) throw std::invalid_argument("Brak przeciecia osi OX.");

        double c = a;

        for (int i = 0; i < max_iter; ++i) {
            c = (a * fb - b * fa) / (fb - fa);
            double fc = f(c);

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
    /// <summary>
    /// Finds sub-intervals in [a, b] where the function f changes sign,
    /// indicating a root may exist within those intervals.
    /// </summary>
    /// <typeparam name="Func">Type of the callable function or functor.</typeparam>
    /// <param name="f">Function for which to find sign-changing intervals.</param>
    /// <param name="a">Start of the interval to search.</param>
    /// <param name="b">End of the interval to search.</param>
    /// <param name="step">Step size for sampling points in [a, b].</param>
    /// <returns>Vector of pairs representing sub-intervals [x, x + step] where f changes sign.</returns>

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