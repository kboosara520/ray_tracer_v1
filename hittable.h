#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"
#include "interval.h"

struct hit_record {
    Point3 point;
    Vec3 normal;
    double t;
    bool front_face;
    void set_face_normal(const Ray &r, const Vec3 &outward_normal);
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray &r, Interval t_interval, hit_record &rec) const = 0;
};

#endif
