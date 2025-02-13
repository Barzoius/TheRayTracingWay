#include "src/utility.hpp"

#include "src/camera.hpp"
#include "src/drawable.hpp" 
#include "src/drawableList.hpp"
#include "src/sphere.hpp"

//  ./build/Debug/theraytracingway.exe > image.ppm

int main()
{
    drawableList world;

    world.Add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.Add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    camera Camera;

    Camera.aspectRatio  = 16.0 / 9.0;
    Camera.WIDTH = 400;
    Camera.samples = 100;

    Camera.render(world);

}