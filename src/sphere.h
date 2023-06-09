#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"
#include "vector3.h"

#include <memory>

namespace ray_tracing {

class Sphere : public Hittable {
public:
    Sphere(const Vector3& center,
           Vector3::ValueType radius,
           std::shared_ptr<Material> material_ptr);

    bool hit(const Ray& ray,
             HitInfo& hit_info,
             Vector3::ValueType min_distance,
             Vector3::ValueType max_distance) const override;

private:
    Vector3 center;

    Vector3::ValueType radius;

    std::shared_ptr<Material> material_ptr;
};

}

#endif
