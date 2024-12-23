#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    Point3 origin;
    Vec3 direction;
  public:
    Ray();
    Ray(const Point3 &origin, const Vec3 &direction);
    const Point3 &getOrigin() const;
    const Vec3 &getDirection() const;
    Point3 at(double d) const;
};

#endif