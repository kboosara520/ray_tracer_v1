#include "sphere.h"

Sphere::Sphere(const Point3 &point, const double &radius, shared_ptr<Material> mat): center{point}, radius{fmax(0, radius)}, mat{mat} {}

bool Sphere::hit(const Ray &r, Interval t_interval, hit_record &rec) const {
    Vec3 oc = center - r.getOrigin();
    double a = r.getDirection().length_squared();
    double h = dot(r.getDirection(), oc);
    double c = oc.length_squared() - radius * radius;
    double discriminant = h * h - a * c;

    if (discriminant < 0) return false;

    double sqrt_disc = sqrt(discriminant);
    double root = (h - sqrt_disc) / a;
    
    if (!t_interval.surrounds(root)) {
        root = (h + sqrt_disc) / a;
        if (!t_interval.surrounds(root)) {
            return false;
        }
    }

    rec.t = root;
    rec.point = r.at(root);
    Vec3 outward_normal = (rec.point - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}
