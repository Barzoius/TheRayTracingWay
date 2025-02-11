#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "ray.hpp"

class hitData
{
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // normals always point out
        front_face = dot(r.GetRaydirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class drawable
{
public:
    virtual ~drawable() = default;

    virtual bool hit(const ray& r, 
                    double tMin,
                    double tMax,
                    hitData& hitInfo) const = 0;
};

#endif  