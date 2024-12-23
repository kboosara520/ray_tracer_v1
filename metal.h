#ifndef METAL_H
#define METAL_H

#include "color.h"
#include "ray.h"
#include "material.h"

class Metal: public Material {
    Color albedo;
    double fuzz;
  public:
    Metal(const Color &c, double fuzz);
    bool scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const override;
};

#endif