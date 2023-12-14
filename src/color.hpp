#ifndef COLOR_H
#define COLOR_H

#include "interval.hpp"
#include "vec3.hpp"
#include <iostream>

inline void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    float r = pixel_color.r;
    float g = pixel_color.g;
    float b = pixel_color.b;

    // Divide the color by the number of samples.
    float scale = 1.0f / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,255] value of each color component.
    static const Interval intensity(0.000, 0.999);
    out << static_cast<int>(255.999 * intensity.clamp(r)) << ' '
        << static_cast<int>(255.999 * intensity.clamp(g)) << ' '
        << static_cast<int>(255.999 * intensity.clamp(b)) << '\n';
}

#endif
