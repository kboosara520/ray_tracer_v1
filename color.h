#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cmath>
#include "vec3.h"
#include "interval.h"

using namespace std;
class Color: public Vec3 {
    Interval intensity{0.000, 0.999};
  public:
    Color();
    Color(double x, double y, double z);
    Color(const Vec3 &v);

    friend ostream &operator<<(ostream &out, const Color &c);
};

Color unit2Color(const Vec3 &v);
double linear2gamma(double component);

#endif