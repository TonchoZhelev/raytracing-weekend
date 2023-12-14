#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.hpp"

class Interval {
    public:
        float min, max;

        Interval(float min, float max) : min(min), max(max) {}

        Interval() : min(+infinity), max(-infinity) {} // Empty interval

        bool contains(float x) const {
            return min <= x && x <= max;
        }

        bool surrounds(float x) const {
            return min < x && x < max;
        }

        float clamp(float x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static const Interval empty;
        static const Interval universe;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);

#endif // INTERVAL_H
