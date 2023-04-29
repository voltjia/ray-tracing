#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "vector3.h"

namespace ray_tracing {

class Dielectric : public Material {
public:
    Dielectric(Vector3::ValueType index_of_refraction);

    bool scatter(const Ray& incident,
                 const Hittable::HitInfo& hit_info,
                 Ray& scattered,
                 Color& attenuation) const override;

private:
    static Vector3::ValueType reflectance(Vector3::ValueType cos,
                                          Vector3::ValueType ref_idx);

    Vector3::ValueType index_of_refraction;
};

}

#endif
