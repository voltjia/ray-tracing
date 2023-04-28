#include "sphere.h"

#include <cmath>

namespace ray_tracing {

Sphere::Sphere(const Vector3& center, Vector3::ValueType radius)
    : center{center}, radius{radius} {}

bool Sphere::hit(const Ray& ray,
                 HitInfo& hit_info,
                 Vector3::ValueType min_distance,
                 Vector3::ValueType max_distance) const {
    auto oc{ray.origin - center};
    auto a{ray.direction.magnitude_sqaured()};
    auto half_b{Vector3::dot(oc, ray.direction)};
    auto c{oc.magnitude_sqaured() - radius * radius};

    auto discriminant{half_b * half_b - a * c};
    if (discriminant < 0) {
        return false;
    }
    auto sqrt_discriminant{std::sqrt(discriminant)};

    auto root{(-half_b - sqrt_discriminant) / a};
    if (root < min_distance || root > max_distance) {
        root = (-half_b + sqrt_discriminant) / a;
        if (root < min_distance || root > max_distance) {
            return false;
        }
    }

    hit_info.point = ray.at(root);
    hit_info.normal = (hit_info.point - center) / radius;
    hit_info.distance = root;

    return true;
}

}
