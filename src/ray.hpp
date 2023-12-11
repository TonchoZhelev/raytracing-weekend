#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
    private:
        point3 _origin;
        vec3 _direction;

    public:
        ray() {}

        ray(const point3 &origin, const vec3 &direction)
            : _origin(origin), _direction(direction) {}

        point3 origin() const { return _origin; }
        vec3 direction() const { return _direction; }

        point3 at(float t) const {
            return _origin + t * _direction;
        }
};

#endif // RAY_H
