#include "camera.h"

namespace ray_tracing {

Camera::Camera(Vector3 lookfrom,
               Vector3 lookat,
               Vector3 viewup,
               Vector3::ValueType vertical_fov,
               Vector3::ValueType aspect_ratio,
               Vector3::ValueType focus_distance,
               Vector3::ValueType aperture)
    : lookfrom{lookfrom},
      lookat{lookat},
      viewup{viewup},
      vertical_fov{vertical_fov},
      aspect_ratio{aspect_ratio},
      focus_distance{focus_distance},
      aperture{aperture} {}

Ray Camera::generate_ray(Vector3::ValueType s, Vector3::ValueType t) const {
    auto rd{lens_radius * random_vector_in_unit_sphere()};
    auto offset{u * rd.x + v * rd.y};
    return Ray{lookfrom + offset,
               viewport_lower_left_corner + s * viewport_horizontal
                       + t * viewport_vertical - lookfrom - offset};
}

}
