#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "color.h"
#include "ray.h"
#include "material.h"

class Lambertian: public Material {
    Color albedo;
  public:
    Lambertian(const Color &c);
    bool scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const override;
};

#endif
