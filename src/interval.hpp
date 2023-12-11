#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.hpp"

class Interval {
    public:
        double min, max;

        Interval(double min, double max) : min(min), max(max) {}

        Interval() : min(+infinity), max(-infinity) {} // Empty interval

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const {
            return min < x && x < max;
        }

        static const Interval empty;
        static const Interval universe;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);

#endif // INTERVAL_H
