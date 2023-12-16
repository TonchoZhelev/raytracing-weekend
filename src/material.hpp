#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.hpp"
#include "rtweekend.hpp"
#include "vec3.hpp"
#include <cmath>

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
        double _fuzz;

    public:
        Metal(const color &albedo, double fuzz) 
            : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1) {}

        bool
        scatter(const ray &r_in, const HitRecord &rec, color &attenuation, ray &scattered) const override {
            vec3 reflected = reflect(r_in.direction().unit(), rec.normal);
            scattered = ray(rec.p, reflected + _fuzz * random_unit_vector());
            attenuation = _albedo;
            return (scattered.direction().dot(rec.normal) > 0);
        }
};

class Dielectric : public IMaterial {
    private:
        double _index_of_refraction;
    public:
        Dielectric(float index_of_refraction) 
            : _index_of_refraction(index_of_refraction) {}

        bool
        scatter(const ray &r_in, const HitRecord &rec, color &attenuation, ray &scattered) const override {
            attenuation = color(1.f, 1.f, 1.f);
            float refraction_ratio = rec.front_face ? (1.0/_index_of_refraction) : _index_of_refraction;

            vec3 unit_direction = r_in.direction().unit();
            float cos_theta = fminf((-unit_direction).dot(rec.normal), 1.0f);
            float sin_theta = sqrtf(1.f - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.f;
            bool has_to_reflect = reflectance(cos_theta, refraction_ratio) > random_float();
            vec3 direction;

            if (cannot_refract || has_to_reflect) {
                direction = reflect(unit_direction, rec.normal);
            } else {
                direction = refract(unit_direction, rec.normal, refraction_ratio);
            }

            scattered = ray(rec.p, direction);
            return true;
        }

    private:
        static float reflectance(float cosine, float ref_idx) {
            // Use Schlick's approximation for reflectance.
            float r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0*r0;
            return r0 + (1 - r0) * powf((1 - cosine), 5);
        }
};

#endif // MATERIAL_H
