#pragma once

#include "Material.hpp"
#include "Utils.hpp"
#include "Hitable.hpp"

class Metal : public Material
{
    Vector3f albedo;
    float roughness;

public:
    Metal(const Vector3f &a, float roughness_) : albedo(a), roughness(roughness_*roughness_) {}

    inline virtual bool scatter(Ray const &r, const HitData &dat, Vector3f &attenuation, Ray &scattered) const
    {
        Vector3f reflected = Utils::reflect(r.direction.normalized(), dat.normal);
        scattered = Ray(dat.point, reflected + roughness * Utils::randomUnitVec());
        attenuation = albedo;
        return scattered.direction.dot(dat.normal) > 0;
    }
};