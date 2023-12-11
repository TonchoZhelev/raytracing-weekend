#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "interval.hpp"
#include "vec3.hpp"

class Sphere : public IHittable {
    private:
        point3 _center;
        float _radius;

    public:
        Sphere(point3 center, float radius) : _center(center), _radius(radius) {}

        bool hit(const ray &r, Interval ray_t, HitRecord &rec) const override {
            vec3 oc = r.origin() - _center;
            float a = r.direction().lengthsq();
            float half_b = oc.dot(r.direction());
            float c = oc.lengthsq() - _radius * _radius;

            float discriminant = half_b * half_b - a * c;
            if (discriminant < 0) {
                return false;
            }
            float sqrtd = sqrtf(discriminant);

            // Find the nearest root that lies in the acceptable range.
            float root = (-half_b - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (-half_b + sqrtd) / a;
                if (!ray_t.surrounds(root)) {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - _center) / _radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }
};

#endif // SPHERE_H
