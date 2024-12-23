#include "interval.h"

Interval::Interval(double min, double max): min{min}, max{max} {}

double Interval::size() const {
    return max - min;
}

bool Interval::contains(double x) const {
    return min <= x && x <= max;
}

bool Interval::surrounds(double x) const {
    return min < x && x < max;
}

double Interval::clamp(double x) const {
    if (x < min) return min;
    else if (x > max) return max;
    return x;
}

const Interval Interval::empty = Interval();
const Interval Interval::universe = Interval(-infinity, infinity);
