#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vector3.h"

#include "utils.h"

#include <cmath>

namespace ray_tracing {

class Camera {
public:
    Camera(Vector3 lookfrom,
           Vector3 lookat,
           Vector3 viewup,
           Vector3::ValueType vertical_fov,
           Vector3::ValueType aspect_ratio);

    Ray generate_ray(Vector3::ValueType s, Vector3::ValueType t) const;

private:
    Vector3::ValueType vertical_fov{degrees_to_radians(90)};

    Vector3::ValueType aspect_ratio{16.0 / 9.0};

    Vector3::ValueType viewport_height{2 * std::tan(vertical_fov / 2)};

    Vector3::ValueType viewport_width{aspect_ratio * viewport_height};

    Vector3::ValueType focal_length{1};

    Vector3 lookfrom{Vector3::zero};

    Vector3 lookat{Vector3::forward};

    Vector3 viewup{Vector3::up};

    Vector3 w{(lookat - lookfrom).normalized()};

    Vector3 u{Vector3::cross(viewup, w).normalized()};

    Vector3 v{Vector3::cross(w, u)};

    Vector3 viewport_horizontal{viewport_width * u};

    Vector3 viewport_vertical{viewport_height * v};

    Vector3 viewport_lower_left_corner{lookfrom - viewport_horizontal / 2
                                       - viewport_vertical / 2 + w};
};

}

#endif
