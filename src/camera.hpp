#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "vec3.hpp"

class Camera {
    public:
        float aspect_ratio = 1.0f; // Ratio of image width over height 
        int   image_width = 100;

        void render(const IHittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            for (int j = 0; j < image_height; ++j) {
                std::clog << "\rScanlines remaining: " << image_height - j << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    vec3 ray_direction = pixel_center - center;
                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }

            std::clog << "\rDone.                       \n";
        }

    private:
        int    image_height;   // Rendered image height
        point3 center;         // Camera center
        point3 pixel00_loc;    // Location of pixel 0, 0
        vec3   pixel_delta_u;  // Offset to pixel to the right
        vec3   pixel_delta_v;  // Offset to pixel below

        void initialize() {
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = point3(0, 0, 0);

            // Determine viewport dimensions.
            float focal_length = 1.0f;
            float viewport_height = 2.0f;
            float viewport_width = viewport_height * (static_cast<float>(image_width)/image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges
            vec3 viewport_u = vec3(viewport_width, 0, 0);
            vec3 viewport_v = vec3(0, -viewport_height, 0);


            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        color ray_color(const ray &r, const IHittable &world) {
            HitRecord rec;
            if (world.hit(r, Interval(0, infinity), rec)) {
                return 0.5f * (rec.normal + color(1.0f, 1.0f, 1.0f));
            }

            vec3 unit_direction = r.direction().unit();
            float a = 0.5f * (unit_direction.y + 1.0f);
            return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
        }
};

#endif // CAMERA_H
