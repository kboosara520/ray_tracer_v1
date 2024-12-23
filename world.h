#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include "hittable.h"

using namespace std;

class World {
    vector<unique_ptr<Hittable>> objects;
  public:
    void add(unique_ptr<Hittable> obj);
    bool hit(const Ray &r, Interval t_interval, hit_record &hrec) const;
};

#endif
