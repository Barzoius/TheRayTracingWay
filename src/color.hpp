#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel)
{
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif