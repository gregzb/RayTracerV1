#pragma once

#include "Material.hpp"
#include "Utils.hpp"
#include "Hitable.hpp"

class Lambertian : public Material
{
    Vector3f albedo;

public:
    Lambertian(Vector3f const &a) : albedo(a) {}

    inline virtual bool scatter(Ray const & r, HitData const &dat, Vector3f &attenuation, Ray &scattered) const
    {
        Vector3f scatter_direction = dat.normal + Utils::randomUnitVec();
        scattered = Ray(dat.point, scatter_direction);
        attenuation = albedo;
        return true;
    }
};