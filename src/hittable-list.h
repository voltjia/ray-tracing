#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <initializer_list>
#include <memory>
#include <vector>

namespace ray_tracing {

class HittableList : public Hittable {
public:
    HittableList() = default;

    HittableList(
            std::initializer_list<std::shared_ptr<Hittable>> hittable_ptrs);

    void add(std::shared_ptr<Hittable> hittable_ptr);

    void clear();

    bool hit(const Ray& ray,
             HitInfo& hit_info,
             Vector3::ValueType min_distance,
             Vector3::ValueType max_distance) const override;

private:
    std::vector<std::shared_ptr<Hittable>> hittable_ptrs;
};

}

#endif
