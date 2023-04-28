#include "hittable.h"

#include "utils.h"

namespace ray_tracing {

bool Hittable::hit(const Ray& ray, HitInfo& hit_info) const {
    constexpr auto default_min_distance{0.001};
    constexpr auto default_max_distance{infinity};
    return hit(ray, hit_info, default_min_distance, default_max_distance);
}

}
