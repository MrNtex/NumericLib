# Metody Numeryczne

This project implements various numerical methods for solving mathematical problems. (Made as a part of Numerical methods class)

## Features

### Approximation
- Least-squares function approximation

### Interpolation Methods
- **Newton Interpolation:** Calculate interpolated values using Newton's method
- **Lagrange Interpolation:** Calculate interpolated values using Lagrange's method

### Numerical Integration
- **Rectangle Method:** Basic numerical integration using rectangles
- **Trapezoid Method:** Numerical integration using trapezoids
- **Simpson's Method:** Numerical integration using Simpson's rule
- **Gauss-Legendre Quadrature:** Advanced numerical integration using Gauss-Legendre quadrature

### Linear Systems
- **Gauss Elimination:** Solve systems of linear equations using Gaussian elimination
- **LU Decomposition:** Solve systems of linear equations using LU decomposition

### Nonlinear Equations
- **Bisection Method:** Find roots using the bisection method
- **Newton's Method:** Find roots using Newton's method (with analytical derivative)
- **Numerical Newton's Method:** Find roots using Newton's method with numerical derivative
- **Secant Method:** Find roots using the secant method
- **False Position (Regula Falsi):** Find roots using the false position method
- **Interval Finding:** Utility to find intervals containing roots

### Ordinary Differential Equations (ODE)
- **Euler's Method:** First-order numerical method for solving ODEs
- **Heun's Method:** Improved Euler method (Runge-Kutta 2nd order)
- **Midpoint Method:** Second-order Runge-Kutta method
- **Runge-Kutta 4th Order:** Classic fourth-order Runge-Kutta method

## Usage

Each numerical method is implemented as a template function, allowing for flexible use with different types of functions. The methods are organized in separate header files for easy inclusion and use.

## 📦 Installation & Usage

Download:

- `NumericLib.lib`
- `include/` directory with the required header files (e.g., `numeric_examples.hpp`)

### 📌 Integrating into Your Visual Studio Project

1. **Copy the `NumericLib.lib` file and `include/` directory into your project folder or somewhere accessible.**

2. In your Visual Studio project:
   → Go to `Project → Properties`

3. Under `C/C++ → General → Additional Include Directories`  
   → Add the path to your `include/` folder

4. Under `Linker → General → Additional Library Directories`  
   → Add the path to the folder containing `NumericLib.lib`

5. Under `Linker → Input → Additional Dependencies`   
   → Add: NumericLib.lib

6. Include the library headers in your code:
```cpp
#include "NumericLib.hpp"
```
7. Build and run your project.

### 📌 Example
```cpp
vector<double> x_vals = { -1.0, 0.0, 1.0, 2.0 };
vector<double> y_vals = { /* corresponding y values */ };
double result = interpolate(test_x, x_vals, y_vals);
```

## Technologies Used

- C++
- Template metaprogramming for flexible function handling 
