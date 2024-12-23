#include "world.h"

void World::add(unique_ptr<Hittable> obj) {
    objects.emplace_back(std::move(obj));
}

bool World::hit(const Ray &r, Interval t_interval, hit_record &hrec) const {
    hit_record temp_rec;
    bool did_hit = false;
    double closest_sofar = t_interval.max;
    for (const auto &object: objects) {
        if (object->hit(r, Interval{t_interval.min, closest_sofar}, temp_rec)) {
            did_hit = true;
            closest_sofar = temp_rec.t;
            hrec = temp_rec;
        }
    }
    return did_hit;
}
