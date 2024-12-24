#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric: public Material {
    double refraction_index;
    static double reflectance(double cosine, double refraction_index);
  public:
    Dielectric(double refraction_index);
    bool scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const override;
};

#endif
