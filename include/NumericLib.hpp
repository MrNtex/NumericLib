#pragma once
#ifndef NUMERICLIB_HPP
#define NUMERICLIB_HPP

#include <vector>
#include "integration/simpson.hpp"
#include "integration/trapezoid.hpp"
#include "integration/rectangle.hpp"
#include "integration/gauss_legendre.hpp"

#include "interpolation/lagrange.hpp"
#include "interpolation/newton.hpp"

#include "liniear_systems/gauss_elimination.hpp"
#include "liniear_systems/lu.hpp"

#include "approximation.hpp"
#include "ode_methods.hpp"
#include "nonliniear.hpp"
#include "utils.hpp"


#endif // !NUMERICLIB_HPP
