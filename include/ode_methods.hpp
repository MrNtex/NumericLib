#pragma once
#include <vector>
#include <stdexcept>

namespace NumericLib {
    namespace ode {

        /// <summary>
        /// Solves an ODE using the Euler method over the interval [a, b] with N steps.
        /// </summary>
        /// <typeparam name="Func">Callable function with signature f(t, y)</typeparam>
        /// <param name="y0">Initial value y(a)</param>
        /// <param name="f">Right-hand side of the ODE dy/dt = f(t, y)</param>
        /// <param name="a">Start of interval</param>
        /// <param name="b">End of interval</param>
        /// <param name="N">Number of steps</param>
        /// <returns>Vector of approximated y values at each time step</returns>
        /// @exception std::invalid_argument Thrown if N <= 0 or b <= a
        template<typename Func>
        std::vector<double> eulerMethod(double y0, Func f, double a, double b, int N) {
            if (N <= 0 || b <= a) throw std::invalid_argument("Invalid parameters: N must be > 0 and b > a.");
            std::vector<double> results;
            double y = y0, t = a, h = (b - a) / N;
            for (int i = 0; i <= N; ++i) {
                results.push_back(y);
                y += h * f(t, y);
                t += h;
            }
            return results;
        }

        /// <summary>
        /// Solves an ODE using Heun's method (improved Euler) over the interval [a, b] with N steps.
        /// </summary>
        /// <typeparam name="Func">Callable function with signature f(t, y)</typeparam>
        /// <param name="y0">Initial value y(a)</param>
        /// <param name="f">Right-hand side of the ODE dy/dt = f(t, y)</param>
        /// <param name="a">Start of interval</param>
        /// <param name="b">End of interval</param>
        /// <param name="N">Number of steps</param>
        /// <returns>Vector of approximated y values at each time step</returns>
        /// <exception cref="std::invalid_argument">Thrown if N <= 0 or b <= a</exception>
        template<typename Func>
        std::vector<double> heunMethod(double y0, Func f, double a, double b, int N) {
            if (N <= 0 || b <= a) throw std::invalid_argument("Invalid parameters: N must be > 0 and b > a.");
            std::vector<double> results;
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

        /// <summary>
        /// Solves an ODE using the midpoint method over the interval [a, b] with N steps.
        /// </summary>
        /// <typeparam name="Func">Callable function with signature f(t, y)</typeparam>
        /// <param name="y0">Initial value y(a)</param>
        /// <param name="f">Right-hand side of the ODE dy/dt = f(t, y)</param>
        /// <param name="a">Start of interval</param>
        /// <param name="b">End of interval</param>
        /// <param name="N">Number of steps</param>
        /// <returns>Vector of approximated y values at each time step</returns>
        /// <exception cref="std::invalid_argument">Thrown if N <= 0 or b <= a</exception>
        template<typename Func>
        std::vector<double> midpointMethod(double y0, Func f, double a, double b, int N) {
            if (N <= 0 || b <= a) throw std::invalid_argument("Invalid parameters: N must be > 0 and b > a.");
            std::vector<double> results;
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

        /// <summary>
        /// Solves an ODE using the classic 4th-order Runge-Kutta method over the interval [a, b] with N steps.
        /// </summary>
        /// <typeparam name="Func">Callable function with signature f(t, y)</typeparam>
        /// <param name="y0">Initial value y(a)</param>
        /// <param name="f">Right-hand side of the ODE dy/dt = f(t, y)</param>
        /// <param name="a">Start of interval</param>
        /// <param name="b">End of interval</param>
        /// <param name="N">Number of steps</param>
        /// <returns>Vector of approximated y values at each time step</returns>
        /// <exception cref="std::invalid_argument">Thrown if N <= 0 or b <= a</exception>
        template<typename Func>
        std::vector<double> rungeKutta4Method(double y0, Func f, double a, double b, int N) {
            if (N <= 0 || b <= a) throw std::invalid_argument("Invalid parameters: N must be > 0 and b > a.");
            std::vector<double> results;
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

    } // namespace ode
} // namespace NumericLib
