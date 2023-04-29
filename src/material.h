#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"

namespace ray_tracing {

class Material {
public:
    virtual bool scatter(const Ray& incident,
                         const Hittable::HitInfo& hit_info,
                         Ray& scattered,
                         Color& attenuation) const
            = 0;
};

}

#endif
