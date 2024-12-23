#include "ray.h"

Ray::Ray() {}
Ray::Ray(const Point3 &origin, const Vec3 &direction): origin{origin}, direction{direction} {}
const Point3 &Ray::getOrigin() const { return origin; }
const Vec3 &Ray::getDirection() const { return direction; }
Point3 Ray::at(double d) const { return origin + d * direction; }
