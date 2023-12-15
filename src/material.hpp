#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.hpp"
#include "vec3.hpp"
#include "hittable.hpp"

class Material {
    public:
        virtual ~Material() = default;

        virtual bool 
        scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const = 0;
};

#endif // MATERIAL_H
