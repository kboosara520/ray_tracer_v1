#include "lambertian.h"

Lambertian::Lambertian(const Color &c): albedo{c} {}

bool Lambertian::scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const {
    Vec3 scatter_direction = hrec.normal + Vec3::random_unit_vector();
    if (scatter_direction.near_zero()) scatter_direction = hrec.normal;
    scattered = Ray{hrec.point, scatter_direction};
    attenuation = albedo;
    return true;
}


