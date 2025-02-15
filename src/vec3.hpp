#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

class vec3
{

public:
    double e[3];

    vec3() : e{0, 0, 0} {}

    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) {return e[i]; }
    
    vec3& operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3& operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    vec3& operator /=(double t)
    {
        return *this *= 1/t;
    }

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 vrand()
    {
        return vec3(drand(), drand(), drand());
    }

    static vec3 vrand(double min, double max)
    {
        return vec3(drand(min, max), drand(min, max), drand(min, max));
    }
    
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(const vec3& v) {
    return v / v.length();
}

inline vec3 nvrand()
{
    while(true)
    {
        auto p = vec3::vrand(-1, 1);
        auto lensq = p.length_squared();

        // we make sure that is not too close to the center where it can become zero
        if(1e-160 < lensq <= 1) 
            return p / sqrt(lensq);
    }
}

inline vec3 generateInHemisphere(const vec3& surfaceNormal)
{
    vec3 v = nvrand();

    if(dot(v, surfaceNormal) > 0.0) 
        return v;
    else
        return -v;
}

#endif