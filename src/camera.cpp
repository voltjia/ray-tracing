#include "camera.h"

namespace ray_tracing {

Camera::Camera(Vector3 lookfrom,
               Vector3 lookat,
               Vector3 viewup,
               Vector3::ValueType vertical_fov,
               Vector3::ValueType aspect_ratio)
    : lookfrom{lookfrom},
      lookat{lookat},
      viewup{viewup},
      vertical_fov{vertical_fov},
      aspect_ratio{aspect_ratio} {}

Ray Camera::generate_ray(Vector3::ValueType s, Vector3::ValueType t) const {
    return Ray{lookfrom,
               viewport_lower_left_corner + s * viewport_horizontal
                       + t * viewport_vertical - lookfrom};
}

}
