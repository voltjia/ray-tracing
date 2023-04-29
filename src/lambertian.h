#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "color.h"
#include "material.h"

namespace ray_tracing {

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo);

    bool scatter(const Ray& incident,
                 const Hittable::HitInfo& hit_info,
                 Ray& scattered,
                 Color& attenuation) const override;

private:
    Color albedo;
};

}

#endif
