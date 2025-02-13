#ifndef COLOR_HPP
#define COLOR_HPP

#include "range.hpp"
#include "vec3.hpp"

#include <iostream>

using color = vec3;

inline double gammaCorrect(double linearComponent)
{
    if(linearComponent > 0)
        return std::sqrt(linearComponent);
    
    return 0;
}

void write_color(std::ostream& out, const color& pixel)
{
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    r = gammaCorrect(r);
    g = gammaCorrect(g);
    b = gammaCorrect(b);


    static const range intensity(0.000, 0.999);

    int rbyte = int(255.999 * intensity.clamp(r));
    int gbyte = int(255.999 * intensity.clamp(g));
    int bbyte = int(255.999 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif