#include "utils.h"

#include <random>

#include <cmath>

namespace ray_tracing {

Vector3::ValueType degrees_to_radians(Vector3::ValueType degrees) {
    return degrees * pi / 180;
}

float random_float(float min, float max) {
    static std::uniform_real_distribution<float> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

float random_float() {
    return random_float(0, 1);
}

double random_double(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

double random_double() {
    return random_double(0, 1);
}

Vector3 random_vector_in_unit_disk() {
    for (;;) {
        auto vec{Vector3{random_float(-1, 1), random_float(-1, 1), 0}};
        if (vec.magnitude_sqaured() < 1) {
            return vec;
        }
    }
}

Vector3 random_vector_in_unit_sphere() {
    for (;;) {
        auto vec{Vector3::random(-1, 1)};
        if (vec.magnitude_sqaured() < 1) {
            return vec;
        }
    }
}

Vector3 random_unit_vector() {
    return random_vector_in_unit_sphere().normalized();
}

bool is_vector_near_zero(const Vector3& vec) {
    constexpr auto epsilon{1e-8};
    return std::fabs(vec.x) < epsilon && std::fabs(vec.y) < epsilon
           && std::fabs(vec.z) < epsilon;
}

Vector3 reflect(const Vector3& v, const Vector3& n) {
    return v - 2 * Vector3::dot(v, n) * n;
}

Vector3 refract(const Vector3& v,
                const Vector3& n,
                Vector3::ValueType refraction_ratio) {
    auto uv{v.normalized()};
    auto cos_theta{std::fmin(Vector3::dot(-uv, n), 1)};
    auto r_out_perp{refraction_ratio * (uv + cos_theta * n)};
    auto r_out_parallel{
            -std::sqrt(std::fabs(1 - r_out_perp.magnitude_sqaured())) * n};
    return r_out_perp + r_out_parallel;
}

}
