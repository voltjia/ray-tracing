#ifndef RAY_H
#define RAY_H

#include "vector3.h"

namespace ray_tracing {

struct Ray {
    Ray(const Vector3& origin, const Vector3& direction);

    Vector3 at(Vector3::ValueType distance) const;

    Vector3 origin;

    Vector3 direction;
};

}

#endif
