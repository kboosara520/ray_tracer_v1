#include "color.h"

Color::Color(): Vec3{} {}
Color::Color(double x, double y, double z): Vec3{x, y, z} {}
Color::Color(const Vec3 &v): Vec3{v} {}

ostream &operator<<(ostream &out, const Color &c) {
    double r = c.intensity.clamp(linear2gamma(c[0])) * 256;
    double g = c.intensity.clamp(linear2gamma(c[1])) * 256;
    double b = c.intensity.clamp(linear2gamma(c[2])) * 256;
    out << static_cast<int>(r) << ' ' << static_cast<int>(g) << ' ' << static_cast<int>(b);
    return out;
}

Color unit2Color(const Vec3 &v) {
    return 0.5 * Vec3{v.x() + 1, v.y() + 1, v.z() + 1};
}

double linear2gamma(double component) {
    return sqrt(component);
}
