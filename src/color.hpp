#ifndef COLOR_H
#define COLOR_H

#include "interval.hpp"
#include "vec3.hpp"
#include <cmath>
#include <iostream>

inline float linear_to_gama(double linear_component) {
    return sqrtf(linear_component);
}

inline void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    float r = pixel_color.r;
    float g = pixel_color.g;
    float b = pixel_color.b;

    // Divide the color by the number of samples.
    float scale = 1.0f / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Apply linear to gama transform
    r = linear_to_gama(r);
    g = linear_to_gama(g);
    b = linear_to_gama(b);

    // Write the translated [0,255] value of each color component.
    static const Interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif
