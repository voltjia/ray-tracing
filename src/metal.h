#ifndef METAL_H
#define METAL_H

#include "color.h"
#include "material.h"
#include "vector3.h"

namespace ray_tracing {

class Metal : public Material {
public:
    Metal(const Color& albedo, Vector3::ValueType fuzz);

    bool scatter(const Ray& incident,
                 const Hittable::HitInfo& hit_info,
                 Ray& scattered,
                 Color& attenuation) const override;

private:
    Color albedo;

    Vector3::ValueType fuzz;
};

}

#endif
