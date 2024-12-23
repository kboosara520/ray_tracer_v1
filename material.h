#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "color.h"

class Material {
  public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const = 0;
};

#endif
