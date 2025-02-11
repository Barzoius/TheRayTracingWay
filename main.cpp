#include "src/utility.hpp"


#include "src/drawable.hpp" 
#include "src/drawableList.hpp"
#include "src/sphere.hpp"


color ray_color(const ray& r, const drawable& world)
{
    hitData info;
    if (world.hit(r, range(0, INF), info)) {
        return 0.5 * (info.normal + color(1,1,1));
    }

    vec3 unit_direction = normalize(r.GetRaydirection());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main()
{


    auto aspectRatio = 16.0 / 9.0;

    int WIDTH = 400;
    int HEIGHT = int(WIDTH / aspectRatio);
    HEIGHT = (HEIGHT < 1) ? 1 : HEIGHT;

    drawableList world;

    world.Add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.Add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    // camera - viewport distance
    auto focalLength = 1.0;
    auto viewHeight = 2.0;
    auto viewWidth = viewHeight * (double(WIDTH)/HEIGHT);

    auto camCenter = point3(0, 0, 0);

    auto pixelRow = vec3(viewWidth, 0, 0);
    auto pixelCol = vec3(0, -viewHeight, 0);

    auto pixelRowDelta = pixelRow / WIDTH;
    auto pixelColDelta = pixelCol / HEIGHT;

    auto viewOriginCorner = camCenter - vec3(0, 0, focalLength) -  pixelRow / 2  - pixelCol / 2 ;

    auto firstPixel = viewOriginCorner + 0.5 * (pixelRowDelta + pixelColDelta);

    std::cout << "P3\n" <<  WIDTH << ' ' << HEIGHT << "\n255\n";

    for (int j = 0; j < HEIGHT; j++)
    {
        std::clog << "\rScanlines remaining: " << (HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < WIDTH; i++)
        {

            auto centerPixel = firstPixel + (i * pixelRowDelta) + (j * pixelColDelta);
            auto rayDir = centerPixel - camCenter;
            
            ray Ray(camCenter, rayDir);

            color pixel = ray_color(Ray, world);
            write_color(std::cout, pixel);

        }
    }
    std::clog << "\rDone.                 \n";


}