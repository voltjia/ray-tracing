#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vector3.h"

namespace ray_tracing {

class Hittable {
public:
    struct HitInfo {
        Vector3 point;

        Vector3 normal;

        Vector3::ValueType distance;
    };

    virtual bool hit(const Ray& ray,
                     HitInfo& hit_info,
                     Vector3::ValueType min_distance,
                     Vector3::ValueType max_distance) const
            = 0;

    virtual bool hit(const Ray& ray, HitInfo& hit_info) const;
};

}

#endif
