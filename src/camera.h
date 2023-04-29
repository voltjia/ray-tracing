#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vector3.h"

#include <cstddef>

namespace ray_tracing {

class Camera {
public:
    Ray generate_ray(Vector3::ValueType u, Vector3::ValueType v) const;

private:
    Vector3::ValueType aspect_ratio{16.0 / 9.0};

    Vector3::ValueType viewport_height{2};

    Vector3::ValueType viewport_width{aspect_ratio * viewport_height};

    Vector3::ValueType focal_length{1};

    Vector3 position{Vector3::zero};

    Vector3 viewport_horizontal{Vector3::right * viewport_width};

    Vector3 viewport_vertical{Vector3::up * viewport_height};

    Vector3 viewport_lower_left_corner{position - viewport_horizontal / 2
                                       - viewport_vertical / 2
                                       + Vector3::forward * focal_length};
};

}

#endif
