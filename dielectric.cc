#include "dielectric.h"

Dielectric::Dielectric(double refraction_index): refraction_index{refraction_index} {}

bool Dielectric::scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const {
    attenuation = Color{1, 1, 1};
    double ref_index = hrec.front_face ? (1 / refraction_index) : refraction_index;
    Vec3 unit_direction = in.getDirection().normalize();
    double cos_theta = fmin(dot(-unit_direction, hrec.normal), 1);
    Vec3 refracted;
    double sin_theta = sqrt(1 - cos_theta * cos_theta);
    // reflect
    if (ref_index * sin_theta > 1 || reflectance(cos_theta, ref_index) > random_double()) 
        refracted = reflect(unit_direction, hrec.normal);
    // refract
    else 
        refracted = refract(unit_direction, hrec.normal, ref_index);
    scattered = Ray{hrec.point, refracted};
    return true;
}

double Dielectric::reflectance(double cosine, double refraction_index) {
    double r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow(1 - cosine, 5);
}
