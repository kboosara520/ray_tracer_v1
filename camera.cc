#include "camera.h"

Camera::Camera(CameraInfo init_info): 
    image_width{init_info.image_width}, 
    image_height{static_cast<int>(image_width / init_info.aspect_ratio)}, 
    samples_per_pixel{init_info.samples_per_pixel},
    defocus_angle{init_info.defocus_angle},
    focus_dist{init_info.focus_dist},
    camera_center{init_info.look_from},
    w{(init_info.look_from - init_info.look_at).unit_vector()},
    u{(cross(init_info.v_up, w)).unit_vector()},
    v{cross(w, u)}
    {
    image_height = (image_height < 1) ? 1 : image_height;
    double theta = deg2rad(init_info.v_fov);
    double h = tan(theta / 2);
    double viewport_height = 2 * h * focus_dist;
    double viewport_width = viewport_height 
                            * (static_cast<double>(image_width)/image_height);

    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    Point3 viewport_upper_left = camera_center 
                                 - (focus_dist * w) 
                                 - viewport_u / 2 
                                 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    double defocus_radius = focus_dist * tan(deg2rad(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

void Camera::render(const World &world) {
    cout << "P3" << endl << image_width << ' ' << image_height << endl << "255" << endl;
    for (int j = 0; j < image_height; ++j) {
        clog << "At line: " << j << endl;
        for (int i = 0; i < image_width; ++i) {
            Vec3 total_c = Vec3{0, 0, 0};
            for (int k = 0; k < samples_per_pixel; ++k) {
                total_c += ray_color(get_ray(i, j), world, max_dept);
            }
            cout << Color{total_c / samples_per_pixel} << endl;
        }
    }
    clog << "Done" << endl;
}

Color Camera::ray_color(const Ray &r, const World &world, const int max_dept) {
    if (max_dept <= 0) return Color{0, 0, 0};
    hit_record hrec;
    if (world.hit(r, Interval{0.001, infinity}, hrec)) {
        Ray scattered;
        Color attenuation;
        if (hrec.mat->scatter(r, hrec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, max_dept - 1);
        }
        return Color{0, 0, 0};
    }
    Vec3 unit_dir = r.getDirection().unit_vector();
    double a = 0.5 * (unit_dir.y() + 1);
    return (1.0 - a) * Color{1.0, 1.0, 1.0} + a * Color{0.5, 0.7, 1.0};
}

Ray Camera::get_ray(int i, int j) const {
    Vec3 offset = sample_square();
    Point3 pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);
    Point3 ray_origin = defocus_angle <= 0 ? camera_center : defocus_disk_sample();
    Point3 ray_direction = pixel_sample - ray_origin;
    return Ray{ray_origin, ray_direction};
}

Vec3 Camera::sample_square()  {
    return Vec3{random_double() - 0.5, random_double() - 0.5, 0};
}

Point3 Camera::defocus_disk_sample() const {
    Point3 p = Vec3::random_in_unit_disk();
    return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}
