#include "camera.hpp"
#include "vec3.hpp"
#include "hittable.hpp"
#include "sphere.hpp"

int main(int argc, char** argv) {
    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5f));
    world.add(std::make_shared<Sphere>(point3(0, -100.5f, -1), 100.0f));

    Camera cam;

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 400;

    cam.render(world);

    return 0;
}
