#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "drawable.hpp"
#include "vec3.hpp"

class Sphere : public drawable
{
private:
    point3 center;
    double radius;
public:
    Sphere(const point3& C, double R)
        : center(C), radius(std::fmax(0,R)) {}
    
    bool hit( const ray& r, 
              range tRange,
              hitData& hitInfo) const override
              {
                vec3 oc = center - r.GetRayOrigin();
                auto a = r.GetRaydirection().length_squared();
                auto h = dot(r.GetRaydirection(), oc);
                auto c = oc.length_squared() - radius*radius;;
                auto discriminant = h*h - a*c; // = the delta in the quadratic function

                if(discriminant < 0)
                    return false;
                
                auto root = (h - std::sqrt(discriminant)) / a;
                
                if(!tRange.surrounds(root))
                {
                    root = (h + std::sqrt(discriminant)) / a;

                    if(!tRange.surrounds(root))
                        return false;
                }

                hitInfo.t = root;
                hitInfo.p = r.at(hitInfo.t);
                vec3 outward_normal = (hitInfo.p - center) / radius;
                hitInfo.set_face_normal(r, outward_normal);

                return true;
              }
};

#endif