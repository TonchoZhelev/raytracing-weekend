#ifndef VEC3_H
#define VEC3_H

#include "rtweekend.hpp"
#include <iostream>
#include <cmath>

struct vec3 {
    union {
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
        float e[3];
    };

    vec3() : e{0, 0, 0} {}
    vec3(float x, float y, float z) : e{x, y, z} {}

    vec3 operator-() const { return vec3(-x, -y, -z); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3& operator*=(float t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3& operator/=(float t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }

    float dot(const vec3 &v) const {
        return x*v.x + y*v.y + z*v.z;
    }

    vec3 cross(const vec3 &v) {
        return vec3(y*v.z - z*v.y,
                    z*v.x - x*v.z,
                    x*v.y - y*v.x);
    }

    vec3 unit() const {
        const float len = length();
        return vec3(x / len,
                    y / len,
                    z / len);
    }

    float length() const { return sqrtf(x*x + y*y + z*z); }

    float lengthsq() const { return x*x + y*y + z*z; }

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimentions.
        float s = 1e-8;
        return (fabsf(e[0]) < s) && (fabsf(e[1]) < s) && (fabsf(e[2]) < s);
    }

    static vec3 random() {
        return vec3(random_float(), random_float(), random_float());
    }

    static vec3 random(float min, float max) {
        return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
    }
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3; // RGB color

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(float t, const vec3 &v) {
    return vec3(t * v.x, t * v.y, t * v.z); 
}

inline vec3 operator*(const vec3 &v, float t) {
    return t * v; 
}

inline vec3 operator/(const vec3 &v, float t) {
    return vec3(v.x / t,
                v.y / t,
                v.z / t);
}

inline float dot(const vec3 &u, const vec3 &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.y*v.z - u.z*v.y,
                u.z*v.x - u.x*v.z,
                u.x*v.y - u.y*v.x);
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p = vec3::random(-1, 1);
        if (p.lengthsq() < 1) {
            return p;
        }
    }
}

inline vec3 random_unit_vector() {
    return random_in_unit_sphere().unit();
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (on_unit_sphere.dot(normal) > 0.0f) { // In the same hemisphere as the normal
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * v.dot(n) * n;
}

#endif // VEC3_H
