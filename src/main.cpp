#include "camera.hpp"
#include "vec3.hpp"
#include "hittable.hpp"
#include "sphere.hpp"
#include "material.hpp"

int main(int const argc, char const *const *const argv) {
    // World
    HittableList world;

    float R = cosf(pi/4);

    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(1.5f);
    auto material_right  = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);

    // auto material_left  = std::make_shared<Lambertian>(color(0,0,1));
    // auto material_right = std::make_shared<Lambertian>(color(1,0,0));

    world.add(std::make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(std::make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    // world.add(std::make_shared<Sphere>(point3( -R, 0.0, -1.0), R, material_left));
    // world.add(std::make_shared<Sphere>(point3(  R, 0.0, -1.0), R, material_right));

    Camera cam;

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov      = 90;
    cam.look_from = point3(-2, 2, 1);
    cam.look_at   = point3(0, 0, -1);
    cam.vup       = vec3(0, 1, 0);

    cam.render(world);

    return 0;
}
