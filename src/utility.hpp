#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


const double INF = std::numeric_limits<double>::infinity();
const double DPI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * DPI / 180.0;
}

inline double drand()
{
    return std::rand() / (RAND_MAX + 1.0);  // [0, 1)
}

inline double drand(double min, double max)
{
    return min + (max-min) * drand(); // [min, max)
}

#include "color.hpp"
#include "range.hpp"
#include "ray.hpp"
#include "vec3.hpp"


#endif 