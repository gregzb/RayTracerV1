#pragma once

#include "Material.hpp"
#include "Utils.hpp"
#include "Hitable.hpp"

class Dielectric : public Material
{
    float ref_idx;

public:
    Dielectric(float ref_idx_) : ref_idx(ref_idx_) {}

    inline virtual bool scatter(Ray const &r, const HitData &dat, Vector3f &attenuation, Ray &scattered) const
    {
        attenuation = Vector3f(1.0, 1.0, 1.0);
        float etai_over_etat;
        if (dat.frontFace)
        {
            etai_over_etat = 1.0 / ref_idx;
        }
        else
        {
            etai_over_etat = ref_idx;
        }

        // if (flag) {
        //     std::cout << "a" << std::endl;
        // }

        Vector3f unit_direction = r.direction.normalized();
        float cos_theta = std::fmin((-unit_direction).dot(dat.normal), 1.0f);
        float sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
        // if (flag)std::cout << "mult: " << etai_over_etat * sin_theta << std::endl;
        if (etai_over_etat * sin_theta >= 1.0 - 0.000001)
        {
            Vector3f reflected = Utils::reflect(unit_direction, dat.normal);
            scattered = Ray(dat.point, reflected);
            return true;
        }

        // if (flag) {
        //     std::cout << "b" << std::endl;
        // }

        float reflect_prob = Utils::schlick(cos_theta, etai_over_etat);
        if (Utils::random() < reflect_prob)
        {
            Vector3f reflected = Utils::reflect(unit_direction, dat.normal);
            scattered = Ray(dat.point, reflected);
            return true;
        }

        // if (flag) {
        //     std::cout << "c" << std::endl;
        // }

        Vector3f refracted = Utils::refract(unit_direction, dat.normal, etai_over_etat);
        // if (flag) {
        //     std::cout << refracted << std::endl;
        // }
        scattered = Ray(dat.point, refracted);
        return true;
    }
};