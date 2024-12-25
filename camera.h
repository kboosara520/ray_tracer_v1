#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "vec3.h"
#include "color.h"
#include "hittable.h"
#include "world.h"
#include "material.h"

using namespace std;

struct CameraInfo {
    int image_width;
    double aspect_ratio;
    int samples_per_pixel;
    double defocus_angle;
    double focus_dist;
    Vec3 look_from;
    Vec3 look_at;
    Vec3 v_up;
    double v_fov;
};

class Camera {
    int max_dept = 50;
    int image_width;
    int image_height;
    int samples_per_pixel;
    double defocus_angle;
    double focus_dist;
    Point3 camera_center;
    Vec3 w, u, v;
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Vec3 defocus_disk_u;
    Vec3 defocus_disk_v;
    Color ray_color(const Ray &r, const World &world, const int max_dept);
    Ray get_ray(int i, int j) const;
    Point3 defocus_disk_sample() const;
    static Vec3 sample_square() ;
  public:
    Camera(CameraInfo init_info);
    void render(const World &world);
};

#endif
