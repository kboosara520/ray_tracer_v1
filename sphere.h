#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include "hittable.h"
#include "vec3.h"
#include "material.h"

using namespace std;

class Sphere: public Hittable {
    Point3 center;
    double radius;
    shared_ptr<Material> mat;
  public:
    Sphere(const Point3 &point, const double &radius, shared_ptr<Material> mat);
    bool hit(const Ray &r, Interval t_interval, hit_record &rec) const override;
};

#endif
