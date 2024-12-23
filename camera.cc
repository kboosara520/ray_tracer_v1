#include "camera.h"

Camera::Camera(int image_width, double aspect_ratio, double focal_length, double viewport_height): image_width{image_width}, image_height{static_cast<int>(image_width / aspect_ratio)} {
    image_height = (image_height < 1) ? 1 : image_height;
    double viewport_width = viewport_height 
                            * (static_cast<double>(image_width)/image_height);

    Vec3 viewport_u = Vec3{viewport_width, 0, 0};
    Vec3 viewport_v = Vec3{0, -viewport_height, 0};

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    Point3 viewport_upper_left = camera_center 
                                 - Vec3{0, 0, focal_length} 
                                 - viewport_u / 2 
                                 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

void Camera::render(const World &world) {
    cout << "P3" << endl << image_width << ' ' << image_height << endl << "255" << endl;
    for (int j = 0; j < image_height; ++j) {
        clog << "At line: " << j << endl;
        for (int i = 0; i < image_width; ++i) {
            Vec3 total_c = Vec3{0, 0, 0};
            for (int k = 0; k < samples_per_pixel; ++k) {
                total_c += ray_color(get_ray(i, j), world);
            }
            cout << Color{total_c / samples_per_pixel} << endl;
        }
    }
    clog << "Done" << endl;
}

Color Camera::ray_color(const Ray &r, const World &world) {
    hit_record hrec;
    bool did_hit = world.hit(r, Interval{0, infinity}, hrec);
    if (did_hit) {
        return unit2Color(hrec.normal);
    }
    Vec3 unit_dir = r.getDirection().unit();
    double a = 0.5 * (unit_dir.y() + 1);
    return (1.0 - a) * Color{1.0, 1.0, 1.0} + a * Color{0.5, 0.7, 1.0};
}

Ray Camera::get_ray(int i, int j) const {
    Vec3 offset = sample_square();
    Point3 pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);
    return Ray{camera_center, pixel_sample - camera_center};
}

Vec3 Camera::sample_square() const {
    return Vec3{random_double() - 0.5, random_double() - 0.5, 0};
}
