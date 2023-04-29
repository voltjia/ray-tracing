#include "lambertian.h"

#include "utils.h"

namespace ray_tracing {

Lambertian::Lambertian(const Color& albedo) : albedo{albedo} {}

bool Lambertian::scatter(const Ray& incident,
                         const Hittable::HitInfo& hit_info,
                         Ray& scattered,
                         Color& attenuation) const {
    auto scatter_direction{hit_info.normal + random_unit_vector()};
    if (is_vector_near_zero(scatter_direction)) {
        scatter_direction = hit_info.normal;
    }
    scattered = Ray{hit_info.point, scatter_direction};
    attenuation = albedo;
    return true;
}

}
