#include <iostream>
#include <cmath>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

float hit_sphere(const point3 &center, float radius, const ray &r) {
    vec3 oc = r.origin() - center;
    float a = r.direction().dot(r.direction());
    float b = 2.0f * oc.dot(r.direction());
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.f;
    } else {
        return (-b - sqrtf(discriminant)) / (2.0f * a);
    }
}

color ray_color(const ray &r) {
    float t = hit_sphere(point3(0, 0, -1), 0.5f, r);
    if (t > 0.0f) {
        vec3 N = (r.at(t) - vec3(0, 0, -1)).unit();
        return 0.5f * color(N.x + 1, N.y + 1, N.z + 1);
    }

    vec3 unit_direction = r.direction().unit();
    float a = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
}

int main(int argc, char** argv) {
    // Image
    float aspect_ratio = 16.0f / 9.0f;
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    float focal_length = 1.0f;
    float viewport_height = 2.0f;
    float viewport_width = viewport_height * (static_cast<float>(image_width)/image_height);
    point3 camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << image_height - j << std::flush;
        for (int i = 0; i < image_width; ++i) {
            point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                       \n";
    return 0;
}
