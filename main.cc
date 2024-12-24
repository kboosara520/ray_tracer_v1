#include <memory>
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
    const int IMAGE_WIDTH = 400;
    const double ASPECT_RATIO = 16.0 / 9.0;

    Camera cam{IMAGE_WIDTH, ASPECT_RATIO};

    World world;
    auto material_ground = make_shared<Lambertian>(Color{0.8, 0.8, 0.0});
    auto material_center = make_shared<Lambertian>(Color{0.1, 0.2, 0.5});
    auto material_left   = make_shared<Dielectric>(1.5);
    auto material_bubble = make_shared<Dielectric>(1.0 / 1.5);
    auto material_right  = make_shared<Metal>(Color{0.8, 0.6, 0.2}, 0.5);

    world.add(make_unique<Sphere>(Point3{0, -100.5, -1}, 100, material_ground));
    world.add(make_unique<Sphere>(Point3{0, 0, -1.2}, 0.5, material_center));
    world.add(make_unique<Sphere>(Point3{-1, 0, -1}, 0.5, material_left));
    world.add(make_unique<Sphere>(Point3{-1, 0, -1}, 0.4, material_bubble));
    world.add(make_unique<Sphere>(Point3{1, 0, -1}, 0.5, material_right));

    cam.render(world);
}
