#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "drawable.hpp"

class camera
{
private:
    int HEIGHT; 

    double samplesScale;

    point3 camCenter;
    point3 firstPixel;
    vec3 pixelRowDelta;
    vec3 pixelColDelta;


public:
    double aspectRatio = 1.0;
    int WIDTH = 100;

    int samples = 10;

    int maxBounces = 10;

    void render(const drawable& world)
    {
        initialize();

        std::cout << "P3\n" <<  WIDTH << ' ' << HEIGHT << "\n255\n";

        for (int j = 0; j < HEIGHT; j++)
        {
            std::clog << "\rScanlines remaining: " << (HEIGHT - j) << ' ' << std::flush;
            
            for (int i = 0; i < WIDTH; i++)
            {
                color pixel(0,0,0);

                for(int sample = 0; sample < samples; sample++)
                {
                    ray Ray = get_ray(i, j);
                    pixel += ray_color(Ray, maxBounces, world);
                }
    
                write_color(std::cout, samplesScale * pixel);
    
            }
        }
        std::clog << "\rDone.                 \n";
    }

private:

    void initialize() 
    {
        HEIGHT = int(WIDTH / aspectRatio);
        HEIGHT = (HEIGHT < 1) ? 1 : HEIGHT;

        samplesScale = 1.0 / samples;

        camCenter = point3(0, 0, 0);

        auto focalLength = 1.0;
        auto viewHeight = 2.0;
        auto viewWidth = viewHeight * (double(WIDTH)/HEIGHT);

        auto pixelRow = vec3(viewWidth, 0, 0);
        auto pixelCol = vec3(0, -viewHeight, 0);
    
        pixelRowDelta = pixelRow / WIDTH;
        pixelColDelta = pixelCol / HEIGHT;

        auto viewOriginCorner = camCenter - vec3(0, 0, focalLength) -  pixelRow / 2  - pixelCol / 2 ;

         firstPixel = viewOriginCorner + 0.5 * (pixelRowDelta + pixelColDelta);

    }

    ray get_ray(int i, int j) const
    {
        vec3 offset = get_sample_region();

        auto samplePixel = firstPixel
                         + ((i + offset.x()) * pixelRowDelta)
                         + ((j + offset.y()) * pixelColDelta);

        auto rayOrigin = camCenter;
        auto rayDirection = samplePixel - rayOrigin;

        return ray(rayOrigin, rayDirection);
    }


    vec3 get_sample_region() const
    {
        // vector to random point in the square [-0.5, 0.5]
        return vec3(drand() - 0.5, drand() -0.5, 0);
    }

    color ray_color(const ray& r, int bounces, const drawable& world)
    {
        if (bounces <= 0)
            return color(0,0,0);

        hitData info;
        
        if (world.hit(r, range(0.001, INF), info)) {
            vec3 dir = info.normal + generateInHemisphere(info.normal);
            return 0.5 * ray_color(ray(info.p, dir), bounces - 1, world);
        }

        vec3 unit_direction = normalize(r.GetRaydirection());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif