#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include <cstddef>
#include <memory>
#include <vector>

struct HitRecord {
    point3 p;
    vec3 normal;
    float t;
    bool front_face;

    void set_face_normal(const ray &r, const vec3 &outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        // assert(outward_normal.length() == 1.0f);

        front_face = r.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class IHittable {
    public:
        // TODO: Might be better to return rec in some way, instead of using it as an out parameter.
        // see the Sphere::hit() method in sphere.hpp for reference.
        virtual bool hit(const ray &r, float ray_tmin, float ray_tmax, HitRecord &rec) const = 0;

        virtual ~IHittable() = default;
};

class HittableList : public IHittable {
    public:
        std::vector<std::shared_ptr<IHittable>> objects;

        HittableList() {}
        HittableList(size_t count) { objects.reserve(count); }
        HittableList(std::shared_ptr<IHittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(std::shared_ptr<IHittable> object) { 
            objects.push_back(object); 
        }

        bool hit(const ray &r, float ray_tmin, float ray_tmax, HitRecord &rec) const override {
            HitRecord temp_rec;
            bool hit_anything = false;
            float closest_so_far = ray_tmax;

            for (const auto &object : objects) {
                bool hit = object->hit(r, ray_tmin, closest_so_far, temp_rec);
                if (hit) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif // HITTABLE_H