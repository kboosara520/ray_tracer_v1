#ifndef INTERVAL_H
#define INTERVAL_H

#include "utility.h"

class Interval {
  public:
    double min, max;
    Interval(double min = infinity, double max = -infinity);
    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const;
    static const Interval empty, universe;
};

#endif
