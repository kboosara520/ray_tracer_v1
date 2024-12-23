#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "vec3.h"
#include "color.h"
#include "hittable.h"
#include "world.h"

using namespace std;

class Camera {
    const int image_width;
    int image_height;
    const int samples_per_pixel = 100;
    Point3 camera_center = Point3{0, 0, 0};
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Color ray_color(const Ray &r, const World &world);
    Ray get_ray(int i, int j) const;
    Vec3 sample_square() const;
  public:
    Camera(int image_width, double aspect_ratio, double focal_length = 1.0, double viewport_height = 2.0);
    void render(const World &world);
};

#endif