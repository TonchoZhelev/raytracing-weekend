#ifndef CAMERA_H
#define CAMERA_H

#include <iomanip>
#include <iostream>
#include <ostream>

#include "rtweekend.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "material.hpp"

class Camera {
    public:
        float aspect_ratio      = 1.0f; // Ratio of image width over height 
        int   image_width       = 100;  // Rendered image width in pixel count
        int   samples_per_pixel = 10;   // Count of random samples for each pixel
        int   max_depth         = 10;   // Maximum number of ray bounces into scene

        float  vfov = 90;                    // Vertical view angle (field of view)
        point3 look_from = point3(0, 0, -1); // Point camera is looking from
        point3 look_at   = point3(0,0,0);    // Point camera is looking at
        vec3   vup       = vec3(0,1,0);      // Camera-relative "up" direction

        void render(const IHittable& world) {
            initialize();

            std::clog << "width: " << image_width << " height: " << image_height << std::endl;
            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            for (int j = 0; j < image_height; ++j) {
                std::clog << "\rScanlines remaining: " << std::setw(3) << image_height - j << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    color pixel_color(0,0,0);

                    for (int sample = 0; sample < samples_per_pixel; ++sample) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_color, samples_per_pixel);
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
        vec3   u, v, w; // Camera frame basis vectors

        void initialize() {
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = look_from;

            // Determine viewport dimensions.
            float focal_length = (look_from - look_at).length();
            float theta = degrees_to_radians(vfov);
            float h = tanf(theta/2);
            float viewport_height = 2 * h * focal_length;
            float viewport_width = viewport_height * (static_cast<float>(image_width)/image_height);

            // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
            w = (look_from - look_at).unit();
            u = vup.cross(w).unit();
            v = w.cross(u);

            // Calculate the vectors across the horizontal and down the vertical viewport edges
            vec3 viewport_u = viewport_width * u;   // Vector across viewport horizontal edge
            vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge


            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            vec3 viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        color ray_color(const ray &r, int depth, const IHittable &world) {
            HitRecord rec;

            // If we've exceeded the ray bounce limit, no more light is gathered.
            if (depth <= 0) {
                return color(0, 0, 0);
            }

            if (world.hit(r, Interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered)) {
                    return attenuation * ray_color(scattered, depth - 1, world);
                }
                return color(0, 0, 0);
            }

            vec3 unit_direction = r.direction().unit();
            float a = 0.5f * (unit_direction.y + 1.0f);
            return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
        }

        ray get_ray(int i, int j) const {
            // Get a randomly sampled camera ray for the pixel at location i,j.

            point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 pixel_sample = pixel_center + pixel_sample_square();

            point3 ray_origin = center;
            vec3 ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const {
            // Returns a random point in the square surrounding a pixel at the origin.
            float px = -0.5f + random_float();
            float py = -0.5f + random_float();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }
};

#endif // CAMERA_H
