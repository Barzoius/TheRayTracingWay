#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


const double INF = std::numeric_limits<double>::infinity();
const double DPI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * DPI / 180.0;
}

#include "color.hpp"
#include "range.hpp"
#include "ray.hpp"
#include "vec3.hpp"


#endif 