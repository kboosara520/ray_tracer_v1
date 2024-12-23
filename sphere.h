#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

using namespace std;

class Sphere: public Hittable {
    Point3 center;
    double radius;
  public:
    Sphere(const Point3 &point, const double &radius);
    bool hit(const Ray &r, Interval t_interval, hit_record &rec) const override;
};

#endif
