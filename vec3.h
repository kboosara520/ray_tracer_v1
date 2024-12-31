#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "utility.h"

class Vec3 {
    double data[3];
  public:
    Vec3();
    Vec3(double x, double y, double z);
    Vec3(const Vec3 &other);
    double x() const;
    double y() const;
    double z() const;
    Vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);
    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(const Vec3 &other) const;
    Vec3 operator/(double d) const;
    Vec3 &operator+=(const Vec3 &other);
    Vec3 &operator-=(const Vec3 &other);
    Vec3 &operator*=(double d);
    Vec3 &operator/=(double d);
    double length() const;
    double length_squared() const;
    Vec3 normalize() const;
    bool near_zero() const;
    static Vec3 random();
    static Vec3 random(double min, double max);
    static Vec3 random_unit_vector();
    // static Vec3 random_on_hemisphere(const Vec3 &normal);
    static Vec3 random_in_unit_disk();
};

using Point3 = Vec3;

std::ostream &operator<<(std::ostream &out, const Vec3 &v);
Vec3 operator*(const Vec3 &v, double d);
Vec3 operator*(double d, const Vec3 &v);
double dot(const Vec3 &u, const Vec3 &v);
Vec3 cross(const Vec3 &u, const Vec3 &v);
Vec3 reflect(const Vec3 &in, const Vec3 &normal);
Vec3 refract(const Vec3 &in, const Vec3 &normal, double etai_over_etat);

#endif
