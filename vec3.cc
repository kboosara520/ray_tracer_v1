#include "vec3.h"

using namespace std;

Vec3::Vec3(): data{0, 0, 0} {}
Vec3::Vec3(double x, double y, double z): data{x, y, z} {}
Vec3::Vec3(const Vec3 &other): data{other[0], other[1], other[2]} {}
double Vec3::x() const { return data[0]; }
double Vec3::y() const { return data[1]; }
double Vec3::z() const { return data[2]; }
Vec3 Vec3::operator-() const { return Vec3{-data[0], -data[1], -data[2]}; }
double Vec3::operator[](int i) const { return data[i]; }
double &Vec3::operator[](int i) { return data[i]; }

Vec3 Vec3::operator+(const Vec3 &other) const {
    return Vec3{data[0] + other[0], data[1] + other[1], data[2] + other[2]};
}

Vec3 Vec3::operator-(const Vec3 &other) const {
    return Vec3{data[0] - other[0], data[1] - other[1], data[2] - other[2]};
}

Vec3 Vec3::operator*(const Vec3 &other) const {
    return Vec3{data[0] * other[0], data[1] * other[1], data[2] * other[2]};
}

Vec3 Vec3::operator/(double d) const {
    return Vec3{data[0] / d, data[1] / d, data[2] / d};
}

Vec3 &Vec3::operator+=(const Vec3 &other) {
    data[0] += other[0];
    data[1] += other[1];
    data[2] += other[2];
    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &other) {
    data[0] -= other[0];
    data[1] -= other[1];
    data[2] -= other[2];
    return *this;
}

Vec3 &Vec3::operator*=(double d) {
    data[0] += d;
    data[1] *= d;
    data[2] *= d;
    return *this;
}

Vec3 &Vec3::operator/=(double d) {
    data[0] /= d;
    data[1] /= d;
    data[2] /= d;
    return *this;
}

double Vec3::length() const {
    return sqrt(length_squared());
}

double Vec3::length_squared() const {
    return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
}

Vec3 Vec3::unit_vector() const {
    return *this / length();
}

bool Vec3::near_zero() const {
    double lower_limit = 1e-8;
    return (fabs(data[0]) < lower_limit) && (fabs(data[1]) < lower_limit) && (fabs(data[2]) < lower_limit);
}

Vec3 Vec3::random() {
    return Vec3{random_double(), random_double(), random_double()};
}

Vec3 Vec3::random(double min, double max) {
    return Vec3{random_double(min, max), random_double(min, max), random_double(min, max)};
}

Vec3 Vec3::random_unit_vector() {
    while (true) {
        Vec3 v = random(-1, 1);
        double lensq = v.length_squared();
        if (1e-160 < lensq && lensq <= 1) return v / sqrt(lensq);
    }
}

Vec3 Vec3::random_on_hemisphere(const Vec3 &normal) {
    Vec3 v = random_unit_vector();
    if (dot(normal, v) >= 0) return v;
    else return -v;
}

ostream &operator<<(ostream &out, const Vec3 &v) {
    out << v[0] << ' ' << v[1] << ' ' << v[2];
    return out;
}

Vec3 operator*(const Vec3 &v, double d) {
    return Vec3{v[0] * d, v[1] * d, v[2] * d};
}

Vec3 operator*(double d, const Vec3 &v) {
    return v * d;
}

double dot(const Vec3 &u, const Vec3 &v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2]; 
}

Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3{
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    };
}

Vec3 reflect(const Vec3 &in, const Vec3 &normal) {
    return in - 2 * dot(in, normal) * normal;
}
