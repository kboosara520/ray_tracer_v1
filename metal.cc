#include "metal.h"

Metal::Metal(const Color &c, double fuzz): albedo{c}, fuzz{fuzz < 1 ? fuzz : 1} {}

bool Metal::scatter(const Ray &in, const hit_record &hrec, Color &attenuation, Ray &scattered) const {
    Vec3 reflected_direction = reflect(in.getDirection(), hrec.normal);
    Vec3 fuzzed_direction = reflected_direction.unit_vector() + (fuzz * Vec3::random_unit_vector());
    scattered = Ray{hrec.point, fuzzed_direction};
    attenuation = albedo;
    return dot(fuzzed_direction, hrec.normal) > 0;
}
