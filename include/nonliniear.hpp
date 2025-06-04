#pragma once
#include <vector>
#include <stdexcept>
#include <utility>

template<typename Func>
double bisection(Func f, double a, double b, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000);

template<typename Func, typename Derivative>
double newton(Func f, double x0, Derivative df, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000);

template<typename Func>
double newton_numeric(Func f, double x0, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000);

template<typename Func>
double secant(Func f, double x0, double x1, std::vector<double>& iter, double a, double b, double tol = 1e-8, int max_iter = 1000);

template<typename Func>
double falsi(Func f, double a, double b, std::vector<double>& iter, double tol = 1e-8, int max_iter = 1000);

template<typename Func>
std::vector<std::pair<double, double>> find_intervals(Func f, double a, double b, double step);
