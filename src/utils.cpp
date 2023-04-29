#include "utils.h"

#include <random>

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

}
