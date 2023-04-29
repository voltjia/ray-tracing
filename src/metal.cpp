#include "metal.h"

#include "utils.h"

#include <cmath>

namespace ray_tracing {

Metal::Metal(const Color& albedo, Vector3::ValueType fuzz)
    : albedo{albedo}, fuzz{std::max(0.0f, std::min(1.0f, fuzz))} {}

bool Metal::scatter(const Ray& incident,
                    const Hittable::HitInfo& hit_info,
                    Ray& scattered,
                    Color& attenuation) const {
    auto reflected{reflect(incident.direction.normalized(), hit_info.normal)};
    scattered = Ray{hit_info.point,
                    reflected + fuzz * random_vector_in_unit_sphere()};
    attenuation = albedo;
    return Vector3::dot(scattered.direction, hit_info.normal) > 0;
}

}
