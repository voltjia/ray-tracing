#ifndef UTILS_H
#define UTILS_H

#include "vector3.h"

#include <limits>

#include <cmath>

namespace ray_tracing {

constexpr auto infinity{std::numeric_limits<Vector3::ValueType>::infinity()};

constexpr auto pi{3.1415926535897932385};

Vector3::ValueType degrees_to_radians(Vector3::ValueType degrees);

float random_float(float min, float max);

float random_float();

double random_double(double min, double max);

double random_double();

Vector3 random_vector_in_unit_disk();

Vector3 random_vector_in_unit_sphere();

Vector3 random_unit_vector();

bool is_vector_near_zero(const Vector3& vec);

Vector3 reflect(const Vector3& v, const Vector3& n);

Vector3 refract(const Vector3& v,
                const Vector3& n,
                Vector3::ValueType refraction_ratio);

}

#endif
