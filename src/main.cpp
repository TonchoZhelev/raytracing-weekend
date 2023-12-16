#include "camera.hpp"
#include "vec3.hpp"
#include "hittable.hpp"
#include "sphere.hpp"
#include "material.hpp"

int main(int const argc, char const *const *const argv) {
    // World
    HittableList world;

    // float R = cosf(pi/4);
    // auto material_left  = std::make_shared<Lambertian>(color(0,0,1));
    // auto material_right = std::make_shared<Lambertian>(color(1,0,0));
    // world.add(std::make_shared<Sphere>(point3( -R, 0.0, -1.0), R, material_left));
    // world.add(std::make_shared<Sphere>(point3(  R, 0.0, -1.0), R, material_right));

    // auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    // auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    // auto material_left   = std::make_shared<Dielectric>(1.5f);
    // auto material_right  = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);
    //
    // world.add(std::make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(std::make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    // world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(std::make_shared<Sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    // world.add(std::make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            point3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<IMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));


    Camera cam;

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 1920;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;

    cam.vfov      = 20;
    cam.look_from = point3(13, 2, 3);
    cam.look_at   = point3(0, 0, 0);
    cam.vup       = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);

    return 0;
}
