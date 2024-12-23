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

using namespace std;

int main() {
    const int IMAGE_WIDTH = 400;
    const double ASPECT_RATIO = 16.0 / 9.0;

    Camera cam{IMAGE_WIDTH, ASPECT_RATIO};

    World world;
    world.add(make_unique<Sphere>(Point3{0, 0, -1}, 0.5));
    world.add(make_unique<Sphere>(Point3{0, -100.5, -1}, 100));

    cam.render(world);
}
