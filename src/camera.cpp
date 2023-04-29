#include "camera.h"

namespace ray_tracing {

Ray Camera::generate_ray(Vector3::ValueType u, Vector3::ValueType v) const {
    return Ray{position,
               viewport_lower_left_corner + u * viewport_horizontal
                       + v * viewport_vertical - position};
}

}
