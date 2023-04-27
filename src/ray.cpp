#include "ray.h"

namespace ray_tracing {

// TODO: Consider checking if `direction` has already been normalized.
Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin{origin}, direction{direction.normalized()} {}

Vector3 Ray::at(Vector3::ValueType distance) const {
    return origin + distance * direction;
}

}
