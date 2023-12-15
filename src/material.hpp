#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.hpp"
#include "vec3.hpp"

struct HitRecord;

class IMaterial {
    public:
        virtual ~IMaterial() = default;

        virtual bool 
        scatter(const ray &r_in, const HitRecord &rec, color &attenuation, ray &scattered) const = 0;
};

class Lambertian : public IMaterial {
    private:
        color _albedo;

    public:
        Lambertian(const color &albedo) : _albedo(albedo) {}

        bool
        scatter(const ray &r_in, const HitRecord &rec, color &attenuation, ray &scattered) const override {
            vec3 scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero()) {
                scatter_direction = rec.normal;
            }

            scattered = ray(rec.p, scatter_direction);
            attenuation = _albedo;
            return true;
        }

};

class Metal : public IMaterial {
    private:
        color _albedo;

    public:
        Metal(const color &albedo) : _albedo(albedo) {}

        bool
        scatter(const ray &r_in, const HitRecord &rec, color &attenuation, ray &scattered) const override {
            vec3 reflected = reflect(r_in.direction().unit(), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = _albedo;
            return true;
        }
};

#endif // MATERIAL_H
