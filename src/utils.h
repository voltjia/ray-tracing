#ifndef UTILS_H
#define UTILS_H

#include "vector3.h"

#include <limits>

namespace ray_tracing {

constexpr auto infinity{std::numeric_limits<Vector3::ValueType>::infinity()};

constexpr auto pi{3.1415926535897932385};

Vector3::ValueType degrees_to_radians(Vector3::ValueType degrees);

float random_float(float min, float max);

float random_float();

double random_double(double min, double max);

double random_double();

}

#endif
