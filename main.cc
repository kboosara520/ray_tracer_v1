#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include "utility.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "world.h"
#include "interval.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

using namespace std;

int main() {
    auto init = chrono::high_resolution_clock::now();
    World world;
    auto ground_material = make_shared<Lambertian>(Color{0.5, 0.5, 0.5});
    world.add(make_unique<Sphere>(Vec3{0, -1000, 0}, 1000, ground_material));
    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            double choose_mat = random_double();
            Point3 center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};
            if ((center - Point3{4, 0, 0}).length() > 0.9) {
                if (choose_mat < 0.78) {
                    Color albedo = Color::random() * Color::random();
                    auto mat = make_shared<Lambertian>(albedo);
                    world.add(make_unique<Sphere>(center, 0.2, mat));
                }
                else if (choose_mat < 0.92) {
                    Color albedo = Color::random(0.5, 1);
                    double fuzz = 0.3;
                    auto mat = make_shared<Metal>(albedo, fuzz);
                    world.add(make_unique<Sphere>(center, 0.2, mat));
                }
                else {
                    auto mat = make_shared<Dielectric>(1.5);
                    world.add(make_unique<Sphere>(center, 0.2, mat));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    auto inside_bubble = make_shared<Dielectric>(1.0 / 1.5);
    world.add(make_unique<Sphere>(Point3{0, 1, 0}, 1.0, material1));
    world.add(make_unique<Sphere>(Point3{0, 1, 0}, 0.9, inside_bubble));

    auto material2 = make_shared<Lambertian>(Color{0.294, 0.2, 0.509});
    world.add(make_unique<Sphere>(Point3{-4, 1, 0}, 1.0, material2));

    auto material3 = make_shared<Metal>(Color{0.7, 0.6, 0.5}, 0.0);
    world.add(make_unique<Sphere>(Point3{4, 1, 0}, 1.0, material3));

    const int IMAGE_WIDTH = 1280;
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int samples_per_pixel = 500;
    const double defocus_angle = 0.6;
    const double focus_dist = 10;
    const Vec3 look_from{13, 2, 3};
    const Vec3 look_at{0, 0, 0};
    const Vec3 v_up{0, 1, 0};
    const double v_fov = 20;

    const CameraInfo init_info{
        IMAGE_WIDTH, ASPECT_RATIO, 
        samples_per_pixel, 
        defocus_angle, 
        focus_dist, 
        look_from, 
        look_at, 
        v_up, 
        v_fov
    };
    Camera cam{init_info};
    auto render_start = chrono::high_resolution_clock::now();
    cam.render(world);
    auto render_end = chrono::high_resolution_clock::now();
    auto init_time = chrono::duration_cast<chrono::seconds>(render_start - init);
    auto render_time = chrono::duration_cast<chrono::seconds>(render_end - render_start);
    auto total_time = chrono::duration_cast<chrono::seconds>(render_end - init);
    clog << "Initialization time: " << init_time.count() << " seconds" << endl;
    clog << "Render time: " << render_time.count() << " seconds" << endl;
    clog << "Total time: " << total_time.count() << " seconds" << endl;
}
