#ifndef RAY_HPP 
#define RAY_HPP

#include "vec3.hpp"

class ray
{
private:
    point3 rayOrigin;
    vec3 rayDirection;

public:
    ray(){}
    
    ray(const point3& origin, const vec3& dir)
     : rayOrigin(origin), rayDirection(dir) {}

    const point3& GetRayOrigin() const { return rayOrigin;}
    const vec3& GetRaydirection() const { return rayDirection;}  

    // returns the advancement of the ray at t
    point3 at(double t) const 
    {
        return rayOrigin + t * rayDirection;
    }
    
};


#endif