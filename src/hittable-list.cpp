#include "hittable-list.h"

namespace ray_tracing {

HittableList::HittableList(
        std::initializer_list<std::shared_ptr<Hittable>> hittable_ptrs)
    : hittable_ptrs{hittable_ptrs} {}

void HittableList::add(std::shared_ptr<Hittable> hittable_ptr) {
    hittable_ptrs.emplace_back(hittable_ptr);
}

void HittableList::clear() {
    hittable_ptrs.clear();
}

bool HittableList::hit(const Ray& ray,
                       HitInfo& hit_info,
                       Vector3::ValueType min_distance,
                       Vector3::ValueType max_distance) const {
    auto hit_anything{false};
    auto closest_distance{max_distance};

    for (const auto& hittable_ptr : hittable_ptrs) {
        HitInfo temp;
        if (hittable_ptr->hit(ray, temp, min_distance, closest_distance)) {
            hit_anything = true;
            closest_distance = temp.distance;
            hit_info = temp;
        }
    }

    return hit_anything;
}

}
