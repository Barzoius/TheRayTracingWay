#include "src/vec3.hpp"
#include "src/color.hpp"

#include <iostream>


int main()
{
    int WIDTH = 256;
    int HEIGHT = 256;

    std::cout << "P3\n" <<  WIDTH << ' ' << HEIGHT << "\n255\n";

    for (int j = 0; j < WIDTH; j++)
    {
        std::clog << "\rScanlines remaining: " << (HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < HEIGHT; i++)
        {
            auto pixel_color = color(double(i)/(WIDTH-1), double(j)/(HEIGHT-1), 0);
            write_color(std::cout, pixel_color);

        }
    }
    std::clog << "\rDone.                 \n";


}