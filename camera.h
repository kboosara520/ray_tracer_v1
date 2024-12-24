#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "vec3.h"
#include "color.h"
#include "hittable.h"
#include "world.h"
#include "material.h"

using namespace std;

class Camera {
    const int image_width;
    int image_height;
    const int samples_per_pixel = 100;
    const int max_dept = 50;
    Point3 camera_center;
    Vec3 w, u, v;
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Color ray_color(const Ray &r, const World &world, const int max_dept);
    Ray get_ray(int i, int j) const;
    Vec3 sample_square() const;
  public:
    Camera(int image_width, double aspect_ratio, Vec3 look_from, Vec3 look_at, Vec3 v_up, double v_fov);
    void render(const World &world);
};

#endif