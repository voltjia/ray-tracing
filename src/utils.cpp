#include "utils.h"

#include <random>

namespace ray_tracing {

Vector3::ValueType degrees_to_radians(Vector3::ValueType degrees) {
    return degrees * pi / 180;
}

double random_double() {
    static std::uniform_real_distribution<double> distribution(0, 1);
    static std::mt19937 generator;
    return distribution(generator);
}

}
