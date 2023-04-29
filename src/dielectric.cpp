#include "dielectric.h"

#include "utils.h"

#include <cmath>

namespace ray_tracing {

Dielectric::Dielectric(Vector3::ValueType index_of_refraction)
    : index_of_refraction{index_of_refraction} {}

bool Dielectric::scatter(const Ray& incident,
                         const Hittable::HitInfo& hit_info,
                         Ray& scattered,
                         Color& attenuation) const {
    auto front_face{Vector3::dot(incident.direction, hit_info.normal) < 0};
    auto refraction_ratio{front_face ? 1 / index_of_refraction
                                     : index_of_refraction};
    auto normal_against_ray{front_face ? hit_info.normal : -hit_info.normal};
    auto cos_theta{
            std::fmin(Vector3::dot(-incident.direction, normal_against_ray),
                      1)};
    auto sin_theta{std::sqrt(1 - cos_theta * cos_theta)};
    if (refraction_ratio * sin_theta > 1
        || reflectance(cos_theta, refraction_ratio) > random_double()) {
        scattered = Ray{hit_info.point,
                        reflect(incident.direction, normal_against_ray)};
    } else {
        scattered = Ray{hit_info.point,
                        refract(incident.direction,
                                normal_against_ray,
                                refraction_ratio)};
    }
    attenuation = Color::white;
    return true;
}

Vector3::ValueType Dielectric::reflectance(Vector3::ValueType cos,
                                           Vector3::ValueType ref_idx) {
    auto r0{(1 - ref_idx) / (1 + ref_idx)};
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cos, 5);
}

}
